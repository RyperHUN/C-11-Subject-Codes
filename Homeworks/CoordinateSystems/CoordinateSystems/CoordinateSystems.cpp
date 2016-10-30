// CoordinateSystems.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "math.h"

class CoordinateSystem2D
{
	enum Systems {
		Local = 0,
		World = 1,
		View = 2,
		ClipSpace = 3,
		Screen = 4
	};

	static auto Transfer(Systems from, Systems to, Vec4 inCoord)
	{
		if (from == to)
			return inCoord;

		if (from < to) // Inverse transforms
			;
		else
		{
			;
		}
	}
};

int main()
{
    return 0;
}

