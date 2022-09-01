#pragma once
#include<iostream>

#define GLEW_STATIC
#define _USE_MATH_DEFINES
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <list>
#include "math.h"
#include "sphereMath.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp> 
#include "loadimage.h"


class CityGroundTiles {
public:
	//UV struct
	struct UV
	{
		float ux, uy, vx, vy;
	};

	
	//Tile Map for city
	int City[7][7] = {
	{5,5,5,5,5,5,5},
	{5,6,0,10,0,7,5},
	{5,3,5,3,5,3,5},
	{5,8,0,2,0,11,5},
	{5,3,5,3,5,3,5},
	{5,1,0,9,0,4,5},
	{5,5,5,5,5,5,5}, };

	CityGroundTiles() {

	}

	~CityGroundTiles() {

	}

	//UVs arranged to match texture source
	//0  {0.750000, 0.666666, 1.000000, 1.000000},
	//1  {0.500000, 0.333333, 0.750000, 0.666666},
	//2  {0.500000, 0.666666, 0.750000, 1.000000},
	//3  {0.000000, 0.666666, 0.250000, 1.000000},
	//4  {0.250000, 0.666666, 0.500000, 1.000000},
	//5  {0.250000, 0.333333, 0.500000, 0.666666},
	//6  {0.750000, 0.333333, 1.000000, 0.666666},
	//7  {0.000000, 0.333333, 0.250000, 0.666666},
	//8  {0.500000, 0.000000, 0.750000, 0.333333},
	//9  {0.000000, 0.000000, 0.250000, 0.333333}, 
	//10 {0.750000, 0.000000, 1.000000, 0.333333},
	//11 {0.250000, 0.000000, 0.500000, 0.333333},

	UV tile_uvs[12] =
	{
		/*U V*/
		{0.750000, 0.666666, 1.000000, 1.000000},
		{0.500000, 0.333333, 0.750000, 0.666666},
		{0.500000, 0.666666, 0.750000, 1.000000},
		{0.000000, 0.666666, 0.250000, 1.000000},
		{0.250000, 0.666666, 0.500000, 1.000000},
		{0.250000, 0.333333, 0.500000, 0.666666},
		{0.750000, 0.333333, 1.000000, 0.666666},
		{0.000000, 0.333333, 0.250000, 0.666666},
		{0.500000, 0.000000, 0.750000, 0.333333},
		{0.000000, 0.000000, 0.250000, 0.333333},
		{0.750000, 0.000000, 1.000000, 0.333333},
		{0.250000, 0.000000, 0.500000, 0.333333},	
	};

	//Draws the ground with correct normal and texture tile
	void drawGround(GLuint * city_tex) {
		UV uv = tile_uvs[City[0][0]];
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, *city_tex);
		glBegin(GL_QUADS);
		glNormal3f(0.f, 1.f, 0.f);

		int tileMapIndex = 0;
		int xt = 0;
		int zt = 0;
		for (int x = -21; x < 21; x += 6) {
			for (int z = -21; z < 21; z +=6) {
				uv = tile_uvs[(City[xt][zt])];
				glTexCoord2f(uv.vx, uv.vy);
				glVertex3f(x, 0, z);
				glTexCoord2f(uv.ux, uv.vy);
				glVertex3f(x + 6, 0, z);
				
				glTexCoord2f(uv.ux, uv.uy);
				glVertex3f(x+6, 0, z+6);
				
				glTexCoord2f(uv.vx, uv.uy);
				glVertex3f(x, 0, z + 6);
				zt++;
			}
			xt++;
			zt = 0;
		}

		
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}
};