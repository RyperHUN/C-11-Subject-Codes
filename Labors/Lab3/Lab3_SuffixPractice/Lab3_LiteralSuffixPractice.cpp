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

///FONTOS ATVENNI A MERETET! - Ekkor ""-vel kell hivni
std::string operator"" _s(const char* str, size_t size)
{
	return std::string(str, size); //Fontos hogy a meretet megkapja a konstruktor, kulonben az elso lezaro nullaig fogja kiirni!
}

int kettoHatvany (int power)
{
	int hatvany = 1;
	for (int i = 0; i < power; i++)
	{
		hatvany = hatvany * 2;
	}
	return hatvany;
}

//Igy siman stringkent fogja ertelmeni!
int operator"" _bin(const char* str)
{
	size_t size  = strlen (str);
	size_t index = size - 1;
	int sum = 0;
	for( int power = 0; power < size; power++, index--)
	{
		sum += ('0' - str[index]) * kettoHatvany (power) * -1;
	}
	return sum;
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

	//Binary literal
	cout << 1111_bin << endl;     // 15
	cout << 10000000_bin << endl; // 128


#ifdef _DEBUG
	int i;
	cin >> i;
#endif
    return 0;
}

