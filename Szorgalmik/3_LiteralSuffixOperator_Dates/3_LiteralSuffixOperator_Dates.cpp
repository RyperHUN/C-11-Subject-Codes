// 3_LiteralSuffixOperator_Dates.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

class Date 
{
	int year  = 0;
	int month = 0;
	int day   = 0;
public:
	int Year ()  { return year;  } const
	int Month () { return month; } const
	int Day ()   { return day;   } const

	explicit Date (string str)
	{
		stringstream iss (str);
		string token;
		vector<string> exploded;
		while (getline (iss, token, '.')) {
			exploded.push_back (token);
		}

		SetYear (exploded);
	}

	void SetYear (const vector<string>& strs)
	{
		for (const string& str : strs) // access by const reference
		{
			if (str.size () > 3) 
			{
				return;
			}
		}
	}

	friend ostream& operator << (ostream &os, Date date) ///TODO Const& el nem mukodik ?!
	{
		os << date.Year () << '.' << date.Month () << '.' << date.Day () << '.' << std::endl;
		return os;
	}
};

Date operator"" _date(const char* str, std::size_t)
{
	return Date (str);
}

int main()
{
	Date d = "2013.08.11"_date;
	//std::cout << d << std::endl;                    /* 2013.08.11. */
	//std::cout << "'99.08.11"_date << std::endl;     /* 1999.08.11. */
	//std::cout << "'12.08.11"_date << std::endl;     /* 2012.08.11. */
	//std::cout << "08.11.2013"_date << std::endl;    /* 2013.08.11. */

    return 0;
}

