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
		player1.Update ();
		float lX = player1.LeftStick_X ();
		float lY = player1.LeftStick_Y ();
		bool downA = player1.GetButtonDown (XButtons.A);
		bool pressedA = player1.GetButtonPressed (XButtons.A);
		int i = 22;
		
	}
    return 0;
}

