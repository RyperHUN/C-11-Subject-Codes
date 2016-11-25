// 10_StdFunction.cpp : Defines the entry point for the console application.
//


#include <functional>
#include <iostream>
#include <cmath>

namespace Ryper{

	template< class T >
	class reference_wrapper {
		static_assert (std::is_class<T>::value, "Only accepts Objects");
		T& _val;
	public:
		reference_wrapper(T &val)
			:_val(val) {}

		/*operator FUNCPTR& () {return _val;}*/
		template< class... Types>
		auto operator() (Types &&... types)
			-> decltype (_val(std::forward<Types>(types)...))
		{
			return _val(std::forward<Types>(types)...);
		}
	};

	//template <typename FUNCPTR>
	//class functionStoringBase {
	//	auto operator() -> decltype (FUNCPTR()) 
	//	{
	//		
	//	}
	//};

	template <typename FUNC>
	class function;


	template <typename RET, typename ... ARGS>
	class function<RET(ARGS...)> {
		using FUNCPTR = RET (ARGS...);
		FUNCPTR* ptr = nullptr;
	public:

		FUNCPTR* operator= (FUNCPTR* fv) {
			ptr = fv;

			return fv;
		}
		FUNCPTR& operator= (FUNCPTR& fv) {
			ptr = fv;

			return fv;
		}
		
		RET operator() (ARGS &&... args)
		{
			if (ptr == nullptr)
				throw std::bad_function_call ();
			return ptr(std::forward<ARGS>(args)...);
		}

		explicit operator bool () {
			return ptr != nullptr;
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
	/*
	f = std::bind(static_cast<double(*)(double, int)>(pow), std::placeholders::_1, 4);
	std::cout << pow(2.3, 4) << "==" << f(2.3) << std::endl;
	*/
	f = nullptr;
	try {
		f(2.3);
	}
	catch (std::bad_function_call &/*e*/) {
		std::cout << "Megint nullptr" << std::endl;
	}
}

