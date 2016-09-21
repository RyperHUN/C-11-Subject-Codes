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
	int Year ()  const { return year;  }
	int Month () const { return month; }
	int Day ()   const { return day;   }

	Date (Date const&) = default; //Using default CopyCTOR

	explicit Date (string str)
	{
		stringstream iss (str);
		string token;
		vector<string> exploded;
		while (getline (iss, token, '.')) {
			exploded.push_back (token);
		}

		SetAttributes (exploded);
	}

private:
	void SetAttributes (const vector<string>& strs)
	{
		SetYear (strs);
		SetMonthDay (strs);
	}

	void SetYear (const vector<string>& strs)
	{
		string yearStr = strs[FindYearIndex (strs)];
		
		size_t index = yearStr.find ("'");
		if (index == string::npos) 
		{
			year = stoi (yearStr);
		}
		else 
		{
			yearStr = yearStr.substr (1);
			int twoDigitNum = stoi (yearStr);
			if (twoDigitNum < 20)
			    year = 2000 + twoDigitNum;
			else
				year = 1900 + twoDigitNum;
		}
	}

	size_t FindYearIndex (const vector<string>& strs)
	{
		for (size_t i = 0; i < strs.size (); i++) 
		{
			if (strs[i].size () >= 3)
				return i;
		}

		return string::npos;
	}

	void SetMonthDay (const vector<string>& strs)
	{
		size_t yearIndex = FindYearIndex (strs);
		if (yearIndex == 0) 
		{
			month = stoi (strs[1]);
			day   = stoi (strs[2]);
		} 
		else if (yearIndex == 2) 
		{
			month = stoi (strs[0]);
			day   = stoi (strs[1]);
		}
	}

public:
	friend ostream& operator << (ostream &os, Date& date) ///TODO Const& el nem mukodik ?! 'int Date::Year(void)': cannot convert 'this' pointer from 'const Date' to 'Date &' why?
	{
		os << date.Year () << '.' << date.Month () << '.' << date.Day () << '.';
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
	std::cout << d << std::endl;                    /* 2013.08.11. */
	std::cout << "'99.08.11"_date << std::endl;     /* 1999.08.11. */
	std::cout << "'12.08.11"_date << std::endl;     /* 2012.08.11. */
	std::cout << "08.11.2013"_date << std::endl;    /* 2013.08.11. */

#ifdef _DEBUG
	int i;
	std::cin >> i;
#endif
    return 0;
}

