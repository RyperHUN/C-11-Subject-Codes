// 10_StdFunction.cpp : Defines the entry point for the console application.
//


#include <functional>
#include <iostream>
#include <cmath>
#include <cstddef>

namespace Ryper{


	template <typename RET, typename ... ARGS>
	class Any {
	private:
		template <typename RETins, typename ... ARGSins>
		class ContainerBase {
		public:
			virtual ~ContainerBase() {}
			virtual ContainerBase *clone() const = 0;
			virtual RETins operator() (ARGSins &&... args) = 0;
		};
		typedef ContainerBase<RET, ARGS...> ContainerBaseT;

		template <typename T, typename RETins, typename ... ARGSins>
		class Container : public ContainerBaseT {
		public:
			T data;
			Container(T const &what) : data(what) {}
			ContainerBaseT *clone() const override
			{
				return new Container<T, RETins, ARGSins...>(*this);
			}
			RETins operator() (ARGSins &&... args) override
			{
				return data(std::forward<ARGS>(args)...);
			}
		};

		ContainerBaseT *ptr;

	public:
		Any() : ptr(nullptr) {}
		Any(Any const &to_copy)
		{
			ptr = to_copy.ptr->clone();
		}
		Any& operator=(Any const& to_copy)
		{
			ContainerBaseT* copy = nullptr;
			if (to_copy.ptr != nullptr)
				copy = to_copy.ptr->clone();
			delete ptr;
			ptr = copy;
			return *this;
		}
		~Any() { delete ptr; }

		template <typename T>
		void set(T const &what)
		{
			ContainerBaseT *newptr = new Container<T, RET, ARGS...>(what);
			delete ptr;
			ptr = newptr;
		}

		RET operator() (ARGS &&... args)
		{
			return (*ptr) (std::forward<ARGS>(args)...);
		}

		void clear()
		{
			delete ptr;
			ptr = nullptr;
		}

		bool is_valid()
		{
			return ptr != nullptr;
		}
	};

	template <typename FUNC>
	class function;


	template <typename RET, typename ... ARGS>
	class function<RET(ARGS...)> {
		
		//Typedefs
		using FUNCPTR = RET (ARGS...);
		using FunctionT = function<RET (ARGS...)>;
		Any<RET, ARGS...> ptr;
	public:
		function () {}
		function (FunctionT& rhs) {
			this->ptr = rhs.ptr;
		}
		function (FunctionT&&) = delete; //Lazy 

		FunctionT& operator= (FUNCPTR* fv) {
			ptr.set(fv);

			return *this;
		}
		
		template <typename T>
		FunctionT& operator= (T const& anything)
		{
			//ptr.set<T>(anything);
			ptr.  template set<T>(anything);

			return *this;
		}

		FunctionT operator= (nullptr_t)
		{
			ptr.clear ();

			return *this;
		}
		FunctionT operator= (FunctionT const& rhs)
		{
			ptr = rhs.ptr;

			return *this;
		}

		
		RET operator() (ARGS &&... args)
		{
			if (!ptr.is_valid ())
				throw std::bad_function_call ();
			return ptr(std::forward<ARGS>(args)...);
		}

		explicit operator bool () {
			return ptr.is_valid ();
		}

		
	};

	
}



int main() {
	//std::function<double(double)> f;
	Ryper::function<double(double)> f;
	

	if (!f)
		std::cout << "Egyelore nullptr" << std::endl;
	
	f = static_cast<double(*)(double)>(sin);
	std::cout << sin(2.3) << "==" << f(2.3) << std::endl;
	
	f = [](double x) { return x*x; };
	std::cout << 2.3*2.3 << "==" << f(2.3) << std::endl;
	
	f = std::bind(static_cast<double(*)(double, double)>(pow), std::placeholders::_1, 4);
	std::cout << pow(2.3, 4) << "==" << f(2.3) << std::endl;

	f = [&](double x) { return x * 2;}; //More test with Lambda
	std::cout << 2 << "==" << f (1.0) << std::endl;

	Ryper::function<double(double)> fCopy = f;
	std::cout << fCopy(2) << "==" << f(2) << std::endl;

	f = nullptr;
	try {
		f(2.3);
	}
	catch (std::bad_function_call &/*e*/) {
		std::cout << "Megint nullptr" << std::endl;
	}
}

