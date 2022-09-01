#pragma once
#include<iostream>

#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <list>
#include "math.h"
#include "loadimage.h"

class Skybox {
	struct UV
	{
		float ux, uy, vx, vy;
	};


	//UV positions for the first cube faces
	UV sprite_uvs[16] =
	{
		{0.000000, 0.000000, 0.166667, 0.166667},
		{0.166667, 0.000000, 0.333334, 0.166667},
		{0.333334, 0.000000, 0.500001, 0.166667},
		{0.500001, 0.000000, 0.666668, 0.166667},
		{0.666668, 0.000000, 0.833335, 0.166667},
		{0.833335, 0.000000, 1.000000, 0.166667},
	};


	Skybox() {

	}

	~Skybox() {

	}

	draw() {
		s
	}

	




};