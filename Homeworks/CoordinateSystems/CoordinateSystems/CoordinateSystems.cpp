// CoordinateSystems.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "math.h"
#include <memory>

// 2D camera
struct Camera {
	float wCx, wCy;	// center in world coordinates
	float wWx, wWy;	// width and height in world coordinates

public:
	Camera() {
		Animate(0);
	}

	Math::Mat4 V() { // view matrix: translates the center to the origin
		return Math::Mat4  (1, 0, 0, -wCx,
							0, 1, 0, -wCy,
							0, 0, 1, 0,
							0, 0, 0, 1);
	}

	Math::Mat4 P() { // projection matrix: scales it to be a square of edge length 2
		return Math::Mat4  (2 / wWx, 0, 0, 0,
							0, 2 / wWy, 0, 0,
							0, 0, 1, 0,
							0, 0, 0, 1);
	}

	Math::Mat4 Vinv() { // inverse view matrix
		return Math::Mat4(1, 0, 0, wCx,
			0, 1, 0, wCy,
			0, 0, 1, 0,
			0, 0, 0, 1);
	}

	Math::Mat4 Pinv() { // inverse projection matrix
		return Math::Mat4(wWx / 2, 0, 0, 0,
			0, wWy / 2, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);
	}

	void setCenter(float x = 0, float y = 0)
	{
		wCx = x;
		wCy = y;
	}
	void increaseScale(float x = 0, float y = 0)
	{
		wWx += x;
		wWy += y;
	}
	void Animate(float t) {
		wCx = 0; //10 * cosf(t);
		wCy = 0;
		wWx = 16;
		wWy = 16;
	}
	void follow(float x, float y)
	{
		wCx = x;
		wCy = y;
	}
};

class CoordinateSystem
{
public:
	enum Systems {
		Local = 0,
		World = 1,
		View = 2,
		ClipSpace = 3,
		Screen = 4
	};

	auto Transfer(Systems from, Systems to, Math::Vec4 inCoord)
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

private:
	std::weak_ptr<Math::Mat4> viewMatrix;
	std::weak_ptr<Math::Mat4> projectionMatrix;

	std::weak_ptr<Math::Mat4> inverseViewMatrix;
	std::weak_ptr<Math::Mat4> inverseProjectionMatrix;
};

int main()
{
    return 0;
}

