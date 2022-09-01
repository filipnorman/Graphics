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


//Draws Cars - If camera is nearby they will stop - simulates taxi drivers
class Car {
public:
	Cylinder wheels = Cylinder(20, 1, 0.8f, 0.1f);
	Cylinder antenna = Cylinder(20, 1, 0.1, 0.01f);
	GLuint* glass;
	GLuint* car;
	Sphere lamps = Sphere(0.05f);
	glm::vec4 resetColour = glm::vec4(0.5, 0.5, 0.5, 1.f);
	glm::vec3 dir;
	float rotation;
	glm::vec3 location;
	int dirIndex;
	int angleIndex;
	glm::vec3 directionlist[4] = { glm::vec3(0.f,0.f, 0.01f),  glm::vec3(0.f,0.f, -0.01f),  glm::vec3(0.01f,0.f, 0.f), glm::vec3(-0.01f, 0.f, 0.f)};
	int carNum;
	
	float angles[4] = { 0.f, 90.f, 180.f, 270.f };

	bool stop = false;


	
	//Initialises car object
	Car(GLuint* glass_, GLuint* car_, glm::vec3 location_, int direction_, int rotation_, int carNum_) {
		glass = glass_;
		car = car_;
		location = location_;
		dirIndex = direction_;
		angleIndex = rotation_;
		dir = directionlist[dirIndex];
		rotation = angles[angleIndex];
		carNum = carNum_;

	}

	~Car() {

	}

	//Draws the car using rectangles and cylinders
	void drawCar() {
		glPushMatrix();
		glTranslatef(0.f, 0.4f, 0.f );
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, *car);
		drawBox(0.3f, 0.3f, 0.3f, 1.f,  1.f);
		glDisable(GL_TEXTURE_2D);
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, *glass);
		glTranslatef(0.f, 0.18f, 0.3f);
		drawBox(0.2f, 0.1f, 0.05f, 1.f, 1.f);
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0.f, -0.15f, 0.4f);
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, *car);
		drawBox(0.3f, 0.15f, 0.2f, 1.f, 1.f);

		glPushMatrix();
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_COLOR_MATERIAL);
		glColor4f(0.937f, 0.718f, 0.f, 1.f);
		glTranslatef(0.15f, 0.0f, 0.2f);
		lamps.draw();
		float position_1[] = { 0.f, 0.f, 0.f, 1.f };     //Provide light for the car
		glLightfv(GL_LIGHT1, GL_POSITION, position_1);
		glTranslatef(-0.30f, 0.0f, 0.f);
		lamps.draw();
		glColor4f(resetColour[0], resetColour[1], resetColour[2], resetColour[3]);
		glDisable(GL_COLOR_MATERIAL);
		float position_2[] = { 0.f, 0.f, 0.f, 1.f };    
		glLightfv(GL_LIGHT1, GL_POSITION, position_2);
		glPopMatrix();
		glTranslatef(0.4f, -0.13f, 0.0f);
		glRotatef(90.f, 0.f, 0.f, 1.f);
		wheels.drawCylinder(glm::vec4(0.f, 0.f, 0.f, 1.f));

		glPopMatrix();
		glPushMatrix();
		glTranslatef(0.f, -0.15f, -0.4f);
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, *car);
		drawBox(0.3f, 0.15f, 0.2f, 1.f, 1.f);
		glTranslatef(0.4f, -0.13f, 0.0f);
		glRotatef(90.f, 0.f, 0.f, 1.f);
		glDisable(GL_TEXTURE_2D);
		wheels.drawCylinder(glm::vec4(0.f,0.f,0.f,1.f));
		glPopMatrix();
		glPopMatrix();

		if (!stop) {
			location += dir;
		}

		changeDirection();


	}

	//Changes the direction of the car based on coordinates
	void changeDirection() {

		if (carNum == 1) {
			if (location.z >= -0.8f && angleIndex == 0) {
				angleIndex = 3;
				dirIndex = 3;
				dir = directionlist[dirIndex];
				rotation = angles[angleIndex];
			}
			if (location.x <= -11.2f && angleIndex == 3) {
				angleIndex = 2;
				dirIndex = 1;
				dir = directionlist[dirIndex];
				rotation = angles[angleIndex];
			}
			if (location.z <= -11.2f && angleIndex == 2) {
				angleIndex = 1;
				dirIndex = 2;
				dir = directionlist[dirIndex];
				rotation = angles[angleIndex];
			}
			if (location.x >= -0.8f && angleIndex == 1) {
				angleIndex = 0;
				dirIndex = 0;
				dir = directionlist[dirIndex];
				rotation = angles[angleIndex];
			}


		}
		else {
			if (location.z <= 0.8f && angleIndex == 2) {
				angleIndex = 1;
				dirIndex = 2;
				dir = directionlist[dirIndex];
				rotation = angles[angleIndex];
			}
			if (location.x >= 11.2f && angleIndex == 1) {
				angleIndex = 0;
				dirIndex = 0;
				dir = directionlist[dirIndex];
				rotation = angles[angleIndex];
			}
			if (location.z >= 11.2f && angleIndex == 0) {
				angleIndex = 3;
				dirIndex = 3;
				dir = directionlist[dirIndex];
				rotation = angles[angleIndex];
			}
			if (location.x <= 0.8f && angleIndex == 3) {
				angleIndex = 2;
				dirIndex = 1;
				dir = directionlist[dirIndex];
				rotation = angles[angleIndex];
			}
		}

	}

	//Interaction Local Trigger - Car stops if camera nearby
	void checkIfStop(glm::vec3 eye) {
		float distance = sqrtf(powf(location.x - eye.x, 2) + powf(location.y - eye.y, 2) + powf(location.z - eye.z, 2));
		if (distance > 2.f) {
			stop = false;
		}
		else {
			stop = true;
		}
		
		
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