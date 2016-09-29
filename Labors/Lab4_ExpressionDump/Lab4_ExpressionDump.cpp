// Lab4_ExpressionDump.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include <iostream>
#include <memory>

using namespace std;


class Expression {
public:
	/* returns value of expression at x */
	virtual double evaluate(double x) const = 0;

	/* outputs expression as string to stream os */
	virtual void print(std::ostream &os) const = 0;

	/* return dynamically allocated derivative expression */
	virtual shared_ptr<Expression> derivative() const = 0;

	/* return dynamically allocated copy of expression */
	virtual Expression * clone() const = 0;

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

	virtual shared_ptr<Expression> derivative() const override {
		return shared_ptr<Constant> {new Constant {0} };
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

	virtual shared_ptr<Expression> derivative() const override {
		return make_shared<Constant> (1);
	}

	virtual Variable * clone() const override {
		return new Variable{ *this };
	}
};


class TwoOperand : public Expression {
public:
	/* create object, adopt dynamically allocated expressions */
	//TwoOperand(Expression *lhs, Expression *rhs) : lhs_{ lhs }, rhs_{ rhs } {}
	TwoOperand(const shared_ptr<Expression>& lhs,const shared_ptr<Expression>& rhs) : lhs_{ lhs }, rhs_{ rhs } {}

	~TwoOperand() {
	}

	/* copy constructor */
	TwoOperand(TwoOperand const & the_other)
		: lhs_{ the_other.lhs_ }, rhs_{ the_other.rhs_ } {
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
	shared_ptr<Expression> lhs_, rhs_; /// NEM KELL KITENNI * ot!
};


class Sum final : public TwoOperand {
public:
	using TwoOperand::TwoOperand;

	virtual shared_ptr<Expression> derivative() const override {
		return shared_ptr<Sum> {new Sum{lhs_->derivative (), rhs_->derivative ()}};
	}

	virtual Sum * clone() const override {
		return new Sum{ *this };
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

	virtual shared_ptr<Expression> derivative() const override {
		return shared_ptr<Sum>{ 
			new Sum {
				shared_ptr<Product>{ new Product { lhs_->derivative(), rhs_} },
				shared_ptr<Product>{ new Product {lhs_, rhs_->derivative() } }
			}
		};
		//Mas szintaktikaval!
		/*return make_shared<Sum> (
			     make_shared<Product>( lhs_->derivative(), rhs_ ),
			     make_shared<Product>(lhs_, rhs_->derivative() )
		);*/
	}

	virtual Product * clone() const override {
		return new Product{ *this };
	}

private:
	virtual char get_operator() const override {
		return '*';
	}

	virtual double do_operator(double lhs, double rhs) const override {
		return lhs * rhs;
	}
};


int main() {
	shared_ptr<Expression > c = make_shared<Product>( 
		make_shared<Constant>( 5 ),
		make_shared<Sum>
		(
			make_shared<Constant>(3 ),
			make_shared<Variable>()
			)
	);
	std::cout << "f(x) = " << *c << std::endl;
	std::cout << "f(3) = " << c->evaluate(3) << std::endl;

	shared_ptr<Expression> cd = c->derivative();
	std::cout << "f'(x) = " << *cd << std::endl;


#ifdef _DEBUG
	int i;
	std::cin >> i;
#endif
}
