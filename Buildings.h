#pragma once
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
#include "Cylinder.h"
#include "Sphere.h"
#include "loadimage.h"


class Buildings {
public:
	GLuint tallBuildingBrick = loadimage("BrickWall.bmp");
	GLuint tallBuildingGlass = loadimage("GlassWall.bmp");
	GLuint tallBuildingOffice = loadimage("officeWall.bmp");
	
	GLuint roofTall = loadimage("roofTall.bmp");

	Cylinder roundBuilding = Cylinder(25, 5, 6.f, 2.f);
	Cylinder squareBuilding = Cylinder(4, 5, 5.f, 0.8f);

	GLuint roofTile = loadimage("RoofBrick.bmp");
	glm::vec4 colBrickOrange = glm::vec4(0.863f, 0.333f, 0.224f, 1.f);
	glm::vec4 colGlassBlue = glm::vec4(0.1373f, 0.6745f, 0.7686f, 1.f);

	glm::vec4 resetColour = glm::vec4(0.5, 0.5, 0.5, 1.f);

	Buildings() {

	}

	~Buildings() {

	}
	//Round Glass Building
	void drawBuilding1() {
		glPushMatrix();
		roundBuilding.drawTexturedCylinder(colGlassBlue, &tallBuildingGlass);
		glTranslatef(0.f, 6.f, 0.f);
		roundBuilding.drawTextruedSlantedCylinder(colGlassBlue, &tallBuildingGlass);
		glPopMatrix();

	}

	//The biggest building, varying width
	void drawBuilding2() {
		glPushMatrix();
		Cylinder squareBuilding = Cylinder(4, 5, 7.f, 0.8f);
		squareBuilding.drawTexturedCylinder(colGlassBlue, &tallBuildingGlass);
		glTranslatef(0.f, 7.f, 0.f);
		squareBuilding.drawTextruedSlantedCylinder(colGlassBlue, &tallBuildingGlass);
		glTranslatef(0.f, (squareBuilding.m_fHeight / squareBuilding.m_iDivisions) * 2 * (3.f / 7.f), 0.f);
		glRotated(180.f, 0.f, 0.f, 1.f);
		squareBuilding = Cylinder(4, 5, 3.f, 0.5f);
		squareBuilding.drawTextruedSlantedCylinder(colGlassBlue, &tallBuildingGlass);
		glRotated(180.f, 0.f, 0.f, 1.f);
		squareBuilding.drawTexturedCylinder(colGlassBlue, &tallBuildingGlass);
		glTranslatef(0.f, 3.f, 0.f);
		squareBuilding.drawTextruedSlantedCylinder(colGlassBlue, &tallBuildingGlass);
		glTranslatef(0.f, (squareBuilding.m_fHeight / squareBuilding.m_iDivisions) * 2 * (2.f / 5.f), 0.f);
		glRotated(180.f, 0.f, 0.f, 1.f);
		squareBuilding = Cylinder(4, 5, 2.f, 0.2f);
		squareBuilding.drawTextruedSlantedCylinder(colGlassBlue, &tallBuildingGlass);
		glRotated(180.f, 0.f, 0.f, 1.f);
		squareBuilding.drawTexturedCylinder(colGlassBlue, &tallBuildingGlass);
		glTranslatef(0.f, 2.f, 0.f);
		squareBuilding.drawTextruedSlantedCylinder(colGlassBlue, &tallBuildingGlass);
		glPopMatrix();

	}

	//Red Brick Residential Building
	void drawBuilding3() {
		glPushMatrix();
		squareBuilding = Cylinder(4, 5, 3.f, 1.f);
		squareBuilding.drawTexturedCylinder(colBrickOrange, &tallBuildingBrick);
		glTranslatef(0.f, 3.f, 0.f);
		squareBuilding.drawConeTextured(0.5f, &roofTile);
		glTranslatef(0.f, 7.f, 0.f);
		glPopMatrix();
	}

	//Hospital
	void drawBuilding4() {
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, tallBuildingOffice);
		drawHospital(1.f, 2.f, 1.f, 4.f, 4.f);
		glPushMatrix();
		glTranslatef(2.f, 0.f, 0.f);
		drawHospital(1.f, 2.f, 2.f, 2.f, 4.f);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(-2.f, 0.f, 0.f);
		drawHospital(1.f, 2.f, 2.f, 2.f, 4.f);
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();

	}


private:
	//Hospital Helper function
	void drawHospital(float x, float y, float z, float max_X, float max_Y)
	{
		glBegin(GL_QUADS);

		// Back face (z = r)

		glNormal3f(0.f, 0.f, 1.f);
		glTexCoord2f(max_X, max_Y);
		glVertex3f(x, y, z);
		glTexCoord2f(max_X, 0.f);
		glVertex3f(x, -y, z);
		glTexCoord2f(0.f, 0.f);
		glVertex3f(-x, -y, z);
		glTexCoord2f(0.f, max_Y);
		glVertex3f(-x, y, z);

		// Near face (z = -r)

		glNormal3f(0.f, 0.f, -1.f);
		glTexCoord2f(max_X, max_Y);
		glVertex3f(x, y, -z);
		glTexCoord2f(0.f, max_Y);
		glVertex3f(-x, y, -z);
		glTexCoord2f(0.f, 0.f);
		glVertex3f(-x, -y, -z);
		glTexCoord2f(max_X, 0.f);
		glVertex3f(x, -y, -z);

		// Right face (x = r)

		glNormal3f(1.f, 0.f, 0.f);
		glTexCoord2f(max_X, max_Y);
		glVertex3f(x, y, z);
		glTexCoord2f(max_X, 0.f);
		glVertex3f(x, y, -z);
		glTexCoord2f(0.f, 0.f);
		glVertex3f(x, -y, -z);
		glTexCoord2f(0.f, max_Y);
		glVertex3f(x, -y, z);

		// Left face (x = -r)
		glNormal3f(-1.f, 0.f, 0.f);
		glTexCoord2f(max_X, max_Y);
		glVertex3f(-x, y, z);
		glTexCoord2f(0.f, max_Y);
		glVertex3f(-x, -y, z);
		glTexCoord2f(0.f, 0.f);
		glVertex3f(-x, -y, -z);
		glTexCoord2f(max_X, 0.f);
		glVertex3f(-x, y, -z);

		// Top face (y = r)
		//The roof is the same as the wall colour
		glNormal3f(0.f, 1.f, 0.f);
		glTexCoord2f(0.f, 0.f);
		glVertex3f(x, y, z);
		glTexCoord2f(0.f, 0.f);
		glVertex3f(-x, y, z);
		glTexCoord2f(0.f, 0.f);
		glVertex3f(-x, y, -z);
		glTexCoord2f(0.f, 0.f);
		glVertex3f(x, y, -z);

		// Bottom face (y = -r)

		glNormal3f(0.f, -1.f, 0.f);
		glTexCoord2f(max_X, max_Y);
		glVertex3f(x, -y, z);
		glTexCoord2f(max_X, 0.f);
		glVertex3f(x, -y, -z);
		glTexCoord2f(0.f, 0.f);
		glVertex3f(-x, -y, -z);
		glTexCoord2f(0.f, max_Y);
		glVertex3f(-x, -y, z);

		glEnd();
	}

};
