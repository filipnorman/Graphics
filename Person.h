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

//Class which handles the movement, animation, and modeling of the human model.
class Person {
public:
	glm::vec4 resetColour = glm::vec4(0.5, 0.5, 0.5, 1.f);
	Cylinder bodyGenerator = Cylinder(20, 5, 0.2f, 0.05f);
    Sphere head = Sphere(0.08f);
	Sphere joints = Sphere(0.03f);
	
	glm::vec3 dir;
	float rotation;
	glm::vec3 location;

	int dirIndex;
	int angleIndex;
	glm::vec3 directionlist[2] = { glm::vec3(0.f,0.f, 0.01f),  glm::vec3(0.f,0.f, -0.01f)};
	float angles[2] = { 90.f, 270.f };
	

	Person() {
		dirIndex = 0;
		angleIndex = 0;
		location = glm::vec3(2.0f, 0.0f, -3.4f);
		dir = directionlist[dirIndex];
		rotation = angles[angleIndex];
	}

	~Person() {

	}

	void draw() {
		// Measures the time for the animation
		static double previousSeconds = 0.0;
		double elapsedSeconds;
		double currentSeconds = glfwGetTime();

		elapsedSeconds = currentSeconds - previousSeconds;
		previousSeconds = currentSeconds;

		static int keyFrame = 0;
		static float aT = 0.f;
		//Angles that control the rotation from the joints
		static float leftShoulderAngleA = 0.f, leftShoulderAngleB = 0.f, rightShoulderAngleA = 0.f, rightShoulderAngleB = 0.f, leftLegAngleA = 0.f, leftLegAngleB = 0.f, rightLegAngleA = 0.f, rightLegAngleB = 0.f;

		float animationTime = 1.5f;
		float numofStage = 2.f;

		aT = fmod(aT + elapsedSeconds, animationTime);
		float aS = numofStage * aT / animationTime;

		// Keyframe animation 2 frames Swinging back and forth
		if (aS < 1.f || aS > 2.f) {    
			if (keyFrame == 0) {
				keyFrame = 1;

				leftShoulderAngleA = leftShoulderAngleB;
				rightShoulderAngleA = rightShoulderAngleB;
				leftLegAngleA = leftLegAngleB;
				rightLegAngleA = rightLegAngleB;

				leftShoulderAngleB = -10.f;
				leftLegAngleB = 10.f;
				rightShoulderAngleB = 10.f;
				rightLegAngleB = -10.f;
			}
		} else {    
			if (keyFrame == 1) {
				keyFrame = 0;
				leftShoulderAngleA = leftShoulderAngleB;
				leftLegAngleA = leftLegAngleB;
				rightShoulderAngleA = rightShoulderAngleB;
				rightLegAngleA = rightLegAngleB;

				leftShoulderAngleB = 10.f;
				leftLegAngleB = -10.f;
				rightShoulderAngleB = -10.f;
				rightLegAngleB = 10.f;
			}
		}

		glPushMatrix();
		// Main Body
		glTranslatef(0.f, 0.5f, 0.f);
		glEnable(GL_COLOR_MATERIAL);
		glColor4f(0.0f, 0.0f, 0.502f, 1.f);
		drawBox(0.1, 0.15, 0.05, 1,1);
		glDisable(GL_COLOR_MATERIAL);
		

		glPushMatrix();
		//===== SECTION = HEAD ===== 
		//Neck
		glTranslatef(0.f, 0.03f, 0.f);
		// Head
		glPushMatrix();
		glTranslatef(0.f, 0.2f, 0.f);
		glEnable(GL_COLOR_MATERIAL);
		glColor4f(0.992f, 0.961f, 0.886f, 1.f);
		head.draw();
		glDisable(GL_COLOR_MATERIAL);
		glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		//==== SECTION = LEFT ARM ====
		glTranslatef(0.15f, 0.11f, 0.f);
		glRotatef((1 - fmod(aS, 1)) * leftShoulderAngleA + fmod(aS, 1) * leftShoulderAngleB, 1.f, 0.f, 0.f);
		joints.draw();
		glPushMatrix();
		glTranslatef(0.f, -0.20f, 0.f);
		bodyGenerator.drawCylinder(glm::vec4(0.992f, 0.961f, 0.886f, 1.f));
		glPopMatrix();
		glPopMatrix();

		
		glPushMatrix();
		//==== SECTION = RIGHT ARM ====
		glPushMatrix();
		glTranslatef(-0.15f, 0.11f, 0.f);
		glRotatef((1 - fmod(aS, 1)) * rightShoulderAngleA + fmod(aS, 1) * rightShoulderAngleB, 1.f, 0.f, 0.f);
		glEnable(GL_COLOR_MATERIAL);
		glColor4f(0.992f, 0.961f, 0.886f, 1.f);
		joints.draw();
		glDisable(GL_COLOR_MATERIAL);
		glPushMatrix();
		glTranslatef(0.f, -0.20f, 0.f);
		bodyGenerator.drawCylinder(glm::vec4(0.992f, 0.961f, 0.886f, 1.f));
		glPopMatrix();
		glPopMatrix();

		glPopMatrix();

		glPushMatrix();
		//==== SECTION = LEFT LEG  ====
		glTranslatef(0.08f, -0.18f, 0.f);
		glRotatef((1 - fmod(aS, 1)) * leftLegAngleA + fmod(aS, 1) * leftLegAngleB, 1.f, 0.f, 0.f);
		glEnable(GL_COLOR_MATERIAL);
		glColor4f(0.0f, 0.0f, 0.502f, 1.f);
		joints.draw();
		glDisable(GL_COLOR_MATERIAL);
		glTranslatef(0.f, -0.20f, 0.f);
		bodyGenerator.drawCylinder(glm::vec4(0.1f, 0.1f, 0.1f, 1.f));
		glPopMatrix();

		glPushMatrix();
		//==== SECTION = RIGHT LEG ====
		glPopMatrix();
		glTranslatef(-0.08f, -0.18f, 0.f);
		glRotatef((1 - fmod(aS, 1)) * rightLegAngleA + fmod(aS, 1) * rightLegAngleB, 1.f, 0.f, 0.f);
		glEnable(GL_COLOR_MATERIAL);
		glColor4f(0.0f, 0.0f, 0.502f, 1.f);
		joints.draw();
		glDisable(GL_COLOR_MATERIAL);
		glTranslatef(0.f, -0.20f, 0.f);
		bodyGenerator.drawCylinder(glm::vec4(0.1f, 0.1f, 0.1f, 1.f));
		glPopMatrix();



		glEnable(GL_COLOR_MATERIAL);
		glColor4f(resetColour[0], resetColour[1], resetColour[2], resetColour[3]);
		glDisable(GL_COLOR_MATERIAL);

		location += dir;
		changeDirection();
	}

	//Changes the walking direction
	void changeDirection() {
			if (location.z >= 8.4f ) {
				angleIndex = 1;
				dirIndex = 1;
				dir = directionlist[dirIndex];
				rotation = angles[angleIndex];
			}

			if (location.z <= -8.4f ) {
				angleIndex = 0;
				dirIndex = 0;
				dir = directionlist[dirIndex];
				rotation = angles[angleIndex];
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