// Lab3_TimeIntrval.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

//void operator"" _name ()

class TimeInterval
{
private:
	int minutes = 0;
public:
	explicit TimeInterval (int minutes) 
		:minutes (minutes)
	{
	
	}
	
	friend ostream& operator<< (ostream& os, const TimeInterval interval)
	{
		os << interval.minutes / 60 << "h " << interval.minutes % 60 << 'm';
		return os;
	}

	static TimeInterval Minutes(int minutes)
	{
		return TimeInterval(minutes);
	}
	static TimeInterval Hour(int hour)
	{
		return TimeInterval(hour * 60);
	}

	TimeInterval operator+(TimeInterval const& rhs)
	{
		return TimeInterval (minutes + rhs.minutes);
	}
};

TimeInterval operator"" _h(unsigned long long int hours)
{
	return TimeInterval::Hour ((int)hours);
}
TimeInterval operator"" _m(unsigned long long int mins)
{
	return TimeInterval::Minutes ((int)mins);
}

///FONTOS ATVENNI A MERETET!
std::string operator"" _s(const char* str, size_t size)
{
	return std::string(str, size); //Fontos hogy a meretet megkapja a konstruktor, kulonben az elso lezaro nullaig fogja kiirni!
}

int main()
{
	//Interval
	TimeInterval il{65};
	std::cout << il << std::endl;

	TimeInterval i2 = 5_h + 79_m;
	std::cout << i2 << std::endl;

	/////////////////////////////////////////////////
	//String conversion
	
	
	std::cout << "Hello"_s + " vilag" << std::endl; //Hello vilag
	std::cout << "hello\0vilag"_s.length() << std::endl;


#ifdef _DEBUG
	int i;
	cin >> i;
#endif
    return 0;
}

