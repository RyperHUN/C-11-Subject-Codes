// XBOXControllerInputTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include "GamePad.h"

int main()
{
	Gamepad player1(1);
	while (player1.Connected ())
	{
		auto state = player1.GetState ();
		float lX = player1.LeftStick_X ();
		float lY = player1.LeftStick_Y ();
	}
    return 0;
}

