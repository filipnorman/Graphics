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
#include "Sphere.h"
#include "Cylinder.h"
#include "loadimage.h"

class TrafficLight {
public:
	//Lighting 

	Cylinder m_Base = Cylinder(20, 1, 0.50f, 0.02f);
	Sphere light = Sphere(0.025f);

	GLuint texture = loadimage("metalText.bmp");



	TrafficLight() {


	}

	~TrafficLight() {

	}

	void draw() {
		
		glPushMatrix();
		m_Base.drawTexturedCylinder(glm::vec4(0.f, 0.f,0.f,1.f), &texture);
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTranslatef(0.0f, 0.50f, 0.f);
		drawBox(0.05f, 0.15f ,0.05f, 1.f, 1.f);
		glDisable(GL_TEXTURE_2D);
		glTranslatef(0.0f, 0.f, 0.05f);
		glEnable(GL_COLOR_MATERIAL);
		
		glColor4f(0.937f, 0.718f, 0.f, 1.f);
		light.draw();
		glDisable(GL_COLOR_MATERIAL);
		glPushMatrix();
		glEnable(GL_COLOR_MATERIAL);
		glTranslatef(0.0f, -0.07f, 0.0f);
		glColor4f(0.f, 0.518f, 0.314f, 1.f);
		
		light.draw();
		glDisable(GL_COLOR_MATERIAL);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0.0f, 0.07f, 0.0f);
		
		glEnable(GL_COLOR_MATERIAL);
		glColor4f(0.722f, 0.118f, 0.0f, 1.f);
		light.draw();
		glColor4f(0.5f, 0.5f, 0.5f, 0.f);
		glDisable(GL_COLOR_MATERIAL);
		
		glPopMatrix();


		glPopMatrix();

	}
private:

	void drawBox(float x, float y, float z, float max_X, float max_Y) {
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
		glTexCoord2f(max_X, max_Y);
		glVertex3f(x, y, z);
		glTexCoord2f(0.f, max_Y);
		glVertex3f(-x, y, z);
		glTexCoord2f(0.f, 0.f);
		glVertex3f(-x, y, -z);
		glTexCoord2f(max_X, 0.f);
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