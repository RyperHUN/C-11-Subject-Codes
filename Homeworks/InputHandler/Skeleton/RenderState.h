#pragma once

#include "vectormath.h"

struct RenderState {
	mat4 M;
	vec3 color;
	//mat4 V, P, Minv;
	//Material* material;
	//Texture* texture;
	//Light* light1;
	//Light* light2;
	//vec3 wEye;
	RenderState()
	{
	}
};