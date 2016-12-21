// 2_FV_Osztaly.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cmath>


class Expression {
public:
	/* returns value of expression at x */
	virtual double evaluate(double x) const = 0;

	/* outputs expression as string to stream os */
	virtual void print(std::ostream &os) const = 0;

	/* return dynamically allocated derivative expression */
	virtual Expression * derivative() const = 0;

	/* return dynamically allocated copy of expression */
	virtual Expression * clone() const = 0;

	/* return dynamically allocated, simplified version.
	* default version is to return the copy of the expression
	* (if the derived class does not implement its own
	* simplification method) */
	virtual Expression * simplify() const {
		return clone();
	}

	Expression() = default;
	Expression(Expression const &) = default;

	virtual ~Expression() {}
};


/* pass print request to virtual print() method */
std::ostream & operator<<(std::ostream & os, Expression const &e) {
	e.print(os);
	return os;
}


class Constant final : public Expression {
private:
	double c_;

public:
	Constant(double c) : c_{ c } {}

	virtual double evaluate(double) const override {
		return c_;
	}

	virtual void print(std::ostream &os) const override {
		os << c_;
	}

	virtual Expression * derivative() const override {
		return new Constant{ 0 };
	}

	virtual Constant * clone() const override {
		return new Constant{ *this };
	}

	double get_value() const {
		return c_;
	}
};


class Variable final : public Expression {
public:
	virtual double evaluate(double x) const override {
		return x;
	}

	virtual void print(std::ostream &os) const override {
		os << 'x';
	}

	virtual Expression * derivative() const override {
		return new Constant{ 1 };
	}

	virtual Variable * clone() const override {
		return new Variable{ *this };
	}
};


class TwoOperand : public Expression {
public:
	/* create object, adopt dynamically allocated expressions */
	TwoOperand(Expression *lhs, Expression *rhs) : lhs_{ lhs }, rhs_{ rhs } {}

	~TwoOperand() {
		delete lhs_;
		delete rhs_;
	}

	/* copy constructor */
	TwoOperand(TwoOperand const & the_other)
		: lhs_{ the_other.lhs_->clone() }, rhs_{ the_other.rhs_->clone() } {
	}

	/* no copy assignment */
	TwoOperand & operator=(TwoOperand const &) = delete;

	virtual double evaluate(double x) const override final {
		return do_operator(lhs_->evaluate(x), rhs_->evaluate(x));
	}

	virtual void print(std::ostream &os) const override final {
		os << '(' << *lhs_ << get_operator() << *rhs_ << ')';
	}

private:
	/* subclass has to provide function to return its operator */
	virtual char get_operator() const = 0;

	/* subclass has to provide function to do the calculation */
	virtual double do_operator(double lhs, double rhs) const = 0;

protected:
	/* left and right hand side operands */
	Expression *lhs_, *rhs_;
};


class Sum final : public TwoOperand {
public:
	using TwoOperand::TwoOperand;

	virtual Expression * derivative() const override {
		return new Sum{ lhs_->derivative(), rhs_->derivative() };
	}

	virtual Sum * clone() const override {
		return new Sum{ *this };
	}

	virtual Expression * simplify() const override {
		Expression * lhs_simpl = lhs_->simplify();
		Expression * rhs_simpl = rhs_->simplify();
		Constant * lhs_cons = dynamic_cast<Constant *>(lhs_simpl);
		Constant * rhs_cons = dynamic_cast<Constant *>(rhs_simpl);
		if (lhs_cons != nullptr && lhs_cons->get_value() == 0.0) {  /* 0 + a = a */
			delete lhs_simpl;   /* = 0 */
			return rhs_simpl;
		}
		if (rhs_cons != nullptr && rhs_cons->get_value() == 0.0) {  /* a + 0 = a */
			delete rhs_simpl;   /* = 0 */
			return lhs_simpl;
		}
		if (lhs_cons != nullptr && rhs_cons != nullptr) {   /* c + c = c */
			double new_value = lhs_cons->get_value() + rhs_cons->get_value();
			delete lhs_simpl;
			delete rhs_simpl;
			return new Constant{ new_value };
		}
		return new Sum{ lhs_simpl, rhs_simpl };
	}


private:
	virtual char get_operator() const override {
		return '+';
	}

	virtual double do_operator(double lhs, double rhs) const override {
		return lhs + rhs;
	}
};


class Product final : public TwoOperand {
public:
	using TwoOperand::TwoOperand;
	virtual Expression * derivative() const override {
		return new Sum{
			new Product{ lhs_->derivative(), rhs_->clone() },
			new Product{ lhs_->clone(), rhs_->derivative() }
		};
	}

	virtual Product * clone() const override {
		return new Product{ *this };
	}

	virtual Expression * simplify() const override {
		Expression * lhs_simpl = lhs_->simplify();
		Expression * rhs_simpl = rhs_->simplify();
		Constant * lhs_cons = dynamic_cast<Constant *>(lhs_simpl);
		Constant * rhs_cons = dynamic_cast<Constant *>(rhs_simpl);
		if (lhs_cons != nullptr && lhs_cons->get_value() == 0.0) {  /* 0 * a = 0 */
			delete rhs_simpl;
			return lhs_simpl;   /* = 0 */
		}
		if (rhs_cons != nullptr && rhs_cons->get_value() == 0.0) {  /* a * 0 = a */
			delete lhs_simpl;
			return rhs_simpl;   /* = 0 */
		}
		if (lhs_cons != nullptr && lhs_cons->get_value() == 1.0) {  /* 1 * a = a */
			delete lhs_simpl;   /* = 1 */
			return rhs_simpl;
		}
		if (rhs_cons != nullptr && rhs_cons->get_value() == 1.0) {  /* a * 1 = a */
			delete rhs_simpl;   /* = 1 */
			return lhs_simpl;
		}
		if (lhs_cons != nullptr && rhs_cons != nullptr) {   /* c * c = c */
			double new_value = lhs_cons->get_value() * rhs_cons->get_value();
			delete lhs_simpl;
			delete rhs_simpl;
			return new Constant{ new_value };
		}
		return new Product{ lhs_simpl, rhs_simpl };
	}

private:
	virtual char get_operator() const override {
		return '*';
	}

	virtual double do_operator(double lhs, double rhs) const override {
		return lhs * rhs;
	}
};

class Function : public Expression 
{
private:
	const Expression * inside;
public:
	Function(Expression *inside) : inside{ inside } {}
	Function(Function const & other)
		: inside{other.inside} 
	{}
	/* no copy assignment */
	Function & operator=(Function const &) = delete;

	virtual Expression * derivative() const override final
	{
		return new Product{
			get_functionDerivative (inside),
			inside->derivative()
		};
	}

	virtual void print(std::ostream & os) const override final
	{
		os << get_functionName ();
		os << '(';
		os << *inside;
		os << ')';
	}
protected:
	//Igy nemkell protectedde tenni az inside ot!
	double inside_eval (double x) const
	{
		return inside->evaluate (x);
	}
private:
	virtual const char* get_functionName() const = 0;
	virtual Expression* get_functionDerivative(const Expression* inside) const = 0;
};

class Sin final : public Function
{
public:
	using Function::Function;

	virtual Sin * clone() const override {
		return new Sin{ *this };
	}
private:
	virtual const char* get_functionName() const override
	{
		return "sin";
	}
	virtual double evaluate(double x) const override
	{
		return sin (inside_eval (x));
	}

	virtual Expression * get_functionDerivative(const Expression* inside) const override;
};

class Cos final : public Function
{
public:
	using Function::Function;
	virtual Cos * clone() const override {
		return new Cos{ *this };
	}
private:
	virtual Expression* get_functionDerivative(const Expression* inside) const override
	{
		return new Product
		{
			new Constant{ -1 },
			new Sin{ inside->clone() }
		};
	}
	virtual const char* get_functionName() const override
	{
		return "cos";
	}
	virtual double evaluate(double x) const override
	{
		return cos(inside_eval (x));
	}
};

Expression * Sin::get_functionDerivative(const Expression* inside) const 
{
	return new Cos{ inside->clone() };
}



int main() {
	Expression *c = new Product{
		new Constant{ 5 },
		new Sum{
		new Constant{ 3 },
		new Variable
	}
	};
	std::cout << "f(x) = " << *c << std::endl;
	std::cout << "f(3) = " << c->evaluate(3) << std::endl;

	Expression *cd = c->derivative();
	std::cout << "f'(x) = " << *cd << std::endl;
	Expression *simp = c->simplify ();

	std::cout << *simp << std::endl;

	delete c;
	delete cd;
	delete simp;

	Expression *funcTest = new Sin {
		new Product {
			new Constant {5},
			new Variable {}
		}
	};

	Expression *funcTestDeriv = funcTest->derivative ();
	std::cout << "sin(5x) : x = 1 := " << funcTest->evaluate (2) << std::endl;
	std::cout << "sin(5x)' = " << *funcTestDeriv << std::endl;
	

	delete funcTest;
	delete funcTestDeriv;

#ifdef _DEBUG
	int i;
	std::cin >> i;
#endif
	return 0;
}
