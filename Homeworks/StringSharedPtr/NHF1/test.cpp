// NHF1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "MyString.h"


using namespace std;


int main()
{
	{
		String empty{}; //Letrehoz uresen
		cout << empty;
		cout << "Init teszt";
		String init {"hello vilag - Init Teszt + Copy"};

		cout << init << endl;

		//Copy with reference counting
		{
			String a = init;
			cout << a << endl;
		}
		String b ("Release Teszt");
		cout << b << endl;
		b = init;   //= operator works, copies the rhs and releases lhs
		cout << b << endl;
	}
	cout << "-------------------------------" << endl;

	{
		cout << "Operator[] teszt" << endl;
		String normal {"ab"};
		String const constCopy = normal;
		String normalCopy = normal;
		cout << "Const expected :" << endl << "a - ab" << endl;
		//operatorCopy[0] = 'c'; const works cannot modify
		cout << constCopy[0] << " - " << normal << endl; //Write is allowed
		normalCopy[0] = 'c';
		cout << "Not Const expected :" << endl << "c - ab" << endl;
		cout << normalCopy[0] << " - " << normal << endl;
	}

	cout << "-------------------------------" << endl;
	{
		cout << "Operator +/+= test" << endl;
		String left ("left");
		String right ("right");
		cout << "+ expected :" << endl << "leftright" << endl;
		cout << left + right << endl;

		left += right;
		cout << "+= expected :" << endl << "leftright" << endl;
		cout << left << endl;
		left[0] = right[0];
	}
	cout << "-------------------------------" << endl;
	{
		cout << "Operator </==/> test" << endl;
		String left("a");
		String right("b");
		String same("a");
		cout << "< expected :" << endl << "a" << endl;
		if( left < right)
			cout << left << endl;

		cout << "== expected :" << endl << "a" << endl;
		if( left == same)
			cout << same << endl;
	}
	cout << "-------------------------------" << endl;
	{ //Operator >>
		cout << "Operator >> test" << endl;
		String reading{"DELETE ME PLEASE"};
		cin >> reading;
		cout << reading;

	}
	/*String a, b, c;
	c = "Hello vilag";*/


	int i;
	cin >> i;
    return 0;
}

