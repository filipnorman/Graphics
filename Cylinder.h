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


//This custom class creates shapes like cylinders, cones, slanted buildings...
class Cylinder {
public:
	//Number of vertical faces
	int m_iSectors;
	//Number of Horizontal faces
	int m_iDivisions;
	GLfloat m_fHeight;
	//Radius of the object
	GLfloat m_fRadius;
	//Vertex Points of cylinder shape configuration
	std::list<glm::vec2> m_lPoints;
	glm::vec4 resetColour = glm::vec4(0.5,0.5,0.5,1.f);

	Cylinder(int m_iSectors_, int m_iDivisions_, GLfloat m_fHeight_, GLfloat m_fRadius_) : m_iSectors(m_iSectors_), m_iDivisions(m_iDivisions_), m_fHeight(m_fHeight_), m_fRadius(m_fRadius_) {
		generatePointList();
	}

	~Cylinder() {

	}

	//Draws a basic cylinder
	void drawCylinder(glm::vec4 colour) {
		glEnable(GL_COLOR_MATERIAL);
		glColor4f(colour[0], colour[1], colour[2], colour[3]);
		drawTop();
		drawMiddle();
		drawBottom();
		glColor4f(resetColour[0], resetColour[1], resetColour[2], resetColour[3]);
		glDisable(GL_COLOR_MATERIAL);
	}

	//Draws Textured Cylinder
	void drawTexturedCylinder(glm::vec4 colour, GLuint* tex) {
		glColor4f(colour[0], colour[1], colour[2], colour[3]);
		drawTop();
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, *tex);
		drawMiddleTextured();
		glDisable(GL_TEXTURE_2D);
		glColor4f(resetColour[0], resetColour[1], resetColour[2], resetColour[3]);
		drawBottom();
	}

	//Draws a slanted Cylinder
	void drawSlantedCylinder(glm::vec4 colour,GLfloat slant) {
		glColor4f(colour[0], colour[1], colour[2], colour[3]);
		drawSlantedTop(slant);
		drawSlantedMiddle(slant);
		glColor4f(resetColour[0], resetColour[1], resetColour[2], resetColour[3]);
		drawBottom();
	}

	//Draws a textured slanted Cylinder. Provide the texture, and the slant is based of the height
	void drawTextruedSlantedCylinder(glm::vec4 colour, GLuint * tex ) {
		GLfloat slant = m_fHeight / m_iDivisions;
		glColor4f(colour[0], colour[1], colour[2], colour[3]);
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, *tex);
		drawSlantedTopTexture(slant);
		drawSlantedMiddleTexture(slant);
		glColor4f(resetColour[0], resetColour[1], resetColour[2], resetColour[3]);
		glDisable(GL_TEXTURE_2D);
		
		drawBottom();
	}

	//Cone textured
	void drawConeTextured(GLfloat length, GLuint* tex) {
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, *tex);
		drawShapeTextureCone(length);
		glDisable(GL_TEXTURE_2D);
		drawBottom();
	}

	//Function for drawing circles out of triangles
	void drawCircle(glm::vec4 colour) {
		GLfloat temp = m_fHeight;
		m_fHeight = 0.f;
		drawTop();
		m_fHeight = 0.000001f;
		drawBottom();
		m_fHeight = temp;
	}

	//Cone 
	void drawCone(GLfloat length) {
		drawShapeCone(length);
		drawBottom();
	}

	//The following methods are setters which reset the vertex points by regenerating them.
	void setSectors(int sectors) {
		m_iSectors = sectors;
		generatePointList();
	}

	void setDivisions(int divisions) {
		m_iDivisions = divisions;
		generatePointList();
	}

	void setRadius(GLfloat radius) {
		m_fRadius = radius;
		generatePointList();
	}

	void setHeight(GLfloat height) {
		m_fHeight = height;
		generatePointList();
	}

private:
	//Private Helper functions
	//These draw the shapes, texture them and calculate the normals.
	void drawTop() {
		glBegin(GL_TRIANGLES);
		int itemsDrawn = 0;
		
		for (std::list<glm::vec2>::iterator point = (m_lPoints).begin(); point != (m_lPoints).end();) {
			if (itemsDrawn != m_iSectors) {
				glm::vec2 vec_1 = *point;
				point++;
				glm::vec2 vec_2 = *point;
				glNormal3f(0.f, 1.f, 0.f);
				glVertex3f(vec_2.x, m_fHeight, vec_2.y);
				glVertex3f(0, m_fHeight, 0); //Can add to make cone
				glVertex3f(vec_1.x, m_fHeight, vec_1.y);
				itemsDrawn++;
			}
			else {
				point++;
			}
		}
		glEnd();
	}

	void drawShapeCone(GLfloat height) {
		glBegin(GL_TRIANGLES);
		glColor4f(0.0f, 0.0f, 1.0f, 1.f); // Blue
		int itemsDrawn = 0;
		for (std::list<glm::vec2>::iterator point = (m_lPoints).begin(); point != (m_lPoints).end();) {
			if (itemsDrawn != m_iSectors) {
				glm::vec2 vec_1 = *point;
				point++;
				glm::vec2 vec_2 = *point;
				
				glVertex3f(vec_2.x, 0, vec_2.y);
				
				glVertex3f(0, height, 0); //Can add to make cone
				
				glVertex3f(vec_1.x, 0, vec_1.y);
				itemsDrawn++;
			}
			else {
				point++;
			}
		}
		glEnd();
	}

	void drawShapeTextureCone(GLfloat height) {
		glBegin(GL_TRIANGLES);
		glColor4f(0.0f, 0.0f, 1.0f, 1.f); // Blue
		int itemsDrawn = 0;
		for (std::list<glm::vec2>::iterator point = (m_lPoints).begin(); point != (m_lPoints).end();) {
			if (itemsDrawn != m_iSectors) {
				glm::vec2 vec_1 = *point;
				point++;
				glm::vec2 vec_2 = *point;
				glTexCoord2f(1.f, 0.f);
				glVertex3f(vec_2.x, 0, vec_2.y);
				glTexCoord2f(0.5f, 1.f);
				glVertex3f(0, height, 0); //Can add to make cone
				glTexCoord2f(0.5f, 0.f);
				glVertex3f(vec_1.x, 0, vec_1.y);
				itemsDrawn++;
			}
			else {
				point++;
			}
		}
		glEnd();
	}


	void drawSlantedTop(GLfloat slant) {
		glBegin(GL_TRIANGLES);
		//glColor4f(0.0f, 0.0f, 1.0f, 1.f); // Blue
		int itemsDrawn = 0;
		int currentSlant = 0;
		int slantIndex = 1;
		for (std::list<glm::vec2>::iterator point = (m_lPoints).begin(); point != (m_lPoints).end();) {
			if (itemsDrawn != m_iSectors) {
				glm::vec2 vec_1 = *point;
				point++;
				glm::vec2 vec_2 = *point;
				int tempSlant = currentSlant;
				currentSlant += slantIndex;
				glVertex3f(vec_2.x, m_fHeight - (slant * (1.0 - vec_2.x/m_fRadius)) , vec_2.y);
				glVertex3f(0, m_fHeight - (slant ) , 0); //Can add to make cone
				glVertex3f(vec_1.x, m_fHeight - (slant * (1.0 - vec_1.x / m_fRadius)), vec_1.y);
				itemsDrawn++;
			}
			else {
				point++;
			}
		}
		glEnd();
	}



	void drawSlantedMiddle(GLfloat slant) {
		glBegin(GL_QUADS);
		glColor4f(0.0f, 0.0f, 1.0f, 1.f); // Blue
		int itemsDrawn = 0;
		for (std::list<glm::vec2>::iterator point = (m_lPoints).begin(); point != (m_lPoints).end();) {
			if (itemsDrawn != m_iSectors) {
				glm::vec2 vec_1 = *point;
				point++;
				glm::vec2 vec_2 = *point;
				glNormal3f((vec_2.x + vec_1.x) / 2.f, 0, (vec_2.y + vec_1.y) / 2.f);
				glVertex3f(vec_1.x, m_fHeight - (slant * (1.0 - vec_1.x / m_fRadius)), vec_1.y);
				glVertex3f(vec_1.x, 0, vec_1.y);
				glVertex3f(vec_2.x, 0, vec_2.y);
				glVertex3f(vec_2.x, m_fHeight - (slant * (1.0 - vec_2.x / m_fRadius)), vec_2.y);
				itemsDrawn++;
			}
			else {
				point++;
			}
		}
		glEnd();
	}

	void drawBottom() {
		glBegin(GL_TRIANGLES);
		int itemsDrawn = 0;
		for (std::list<glm::vec2>::iterator point = (m_lPoints).begin(); point != (m_lPoints).end();) {
			if (itemsDrawn != m_iSectors) {
				glm::vec2 vec_1 = *point;
				point++;
				glm::vec2 vec_2 = *point;
				glNormal3f(0.f, -1.f, 0.f);
				glVertex3f(vec_1.x, 0, vec_1.y);
				glVertex3f(0, 0, 0);
				glVertex3f(vec_2.x, 0, vec_2.y);
				itemsDrawn++;
			}
			else {
				point++;
			}
		}
		glEnd();
	}

	void drawMiddle() {
		glBegin(GL_QUADS);
		int itemsDrawn = 0;
		GLfloat heightChunck = m_fHeight / m_iDivisions;
		for (std::list<glm::vec2>::iterator point = (m_lPoints).begin(); point != (m_lPoints).end();) {
			if (itemsDrawn != m_iSectors) {
				glm::vec2 vec_1 = *point;
				point++;
				glm::vec2 vec_2 = *point;
				for (int i = 1; i <= m_iDivisions; i++) {
					glNormal3f((vec_2.x + vec_1.x) / 2.f, 0, (vec_2.y + vec_1.y) / 2.f);
					glVertex3f(vec_1.x, heightChunck * i, vec_1.y);
					glVertex3f(vec_1.x, heightChunck * (i - 1), vec_1.y);
					glVertex3f(vec_2.x, heightChunck * (i - 1), vec_2.y);
					glVertex3f(vec_2.x, heightChunck * i, vec_2.y);
				}
				itemsDrawn++;
			} else {
				point++;
			}
		}
		glEnd();
	}

	void drawMiddleTextured() {
		glBegin(GL_QUADS);
		glColor4f(0.0f, 0.0f, 1.0f, 1.f); // Blue
		int itemsDrawn = 0;
		GLfloat heightChunck = m_fHeight / m_iDivisions;
		for (std::list<glm::vec2>::iterator point = (m_lPoints).begin(); point != (m_lPoints).end();) {
			if (itemsDrawn != m_iSectors) {
				glm::vec2 vec_1 = *point;
				point++;
				glm::vec2 vec_2 = *point;
				for (int i = 1; i <= m_iDivisions; i++) {
					glNormal3f((vec_2.x + vec_1.x) / 2.f, 0, (vec_2.y + vec_1.y) / 2.f);
					glTexCoord2f(0.f, 1.f);
					glVertex3f(vec_1.x, heightChunck * i, vec_1.y);
					glTexCoord2f(0.f, 0.f);
					glVertex3f(vec_1.x, heightChunck * (i - 1), vec_1.y);
					glTexCoord2f(1.f, 0.f);
					glVertex3f(vec_2.x, heightChunck * (i - 1), vec_2.y);
					glTexCoord2f(1.f, 1.f);
					glVertex3f(vec_2.x, heightChunck * i, vec_2.y);
				}
				itemsDrawn++;
			}
			else {
				point++;
			}
		}
		glEnd();
	}


	void drawSlantedTopTexture(GLfloat slant) {
		glBegin(GL_TRIANGLES);
		//glColor4f(0.0f, 0.0f, 1.0f, 1.f); // Blue
		int itemsDrawn = 0;
		int currentSlant = 0;
		int slantIndex = 1;
		float currentPointAngle = 0;
		for (std::list<glm::vec2>::iterator point = (m_lPoints).begin(); point != (m_lPoints).end();) {
			if (itemsDrawn != m_iSectors) {
				glm::vec2 vec_1 = *point;
				point++;
				glm::vec2 vec_2 = *point;
				int tempSlant = currentSlant;
				currentSlant += slantIndex;
				float temp = currentPointAngle;
				itemsDrawn++;
				currentPointAngle = (2 * M_PI / m_iSectors) * itemsDrawn;

				glTexCoord2f(1.f * sinf(currentPointAngle), 1.f + 1.f * cosf(currentPointAngle));
				glVertex3f(vec_2.x, slant*2 - (slant * (1.0 - vec_2.x / m_fRadius)), vec_2.y);
				glTexCoord2f(0.f, 0.f);
				glVertex3f(0, slant*2 - (slant), 0); 
				glTexCoord2f(1.f * sinf(temp), 1.f + 1.f * cosf(temp));
				glVertex3f(vec_1.x, slant*2 - (slant * (1.0 - vec_1.x / m_fRadius)), vec_1.y);
			}
			else {
				point++;
			}
		}
		glEnd();
	}


	void drawSlantedMiddleTexture(GLfloat slant) {
		glBegin(GL_QUADS);
		glColor4f(0.0f, 0.0f, 1.0f, 1.f); // Blue
		int itemsDrawn = 0;
		float currentPointAngle = 0;
		for (std::list<glm::vec2>::iterator point = (m_lPoints).begin(); point != (m_lPoints).end();) {
			if (itemsDrawn != m_iSectors) {
				glm::vec2 vec_1 = *point;
				point++;
				glm::vec2 vec_2 = *point;
				float temp = currentPointAngle;
				itemsDrawn++;
				currentPointAngle = (2 * M_PI / m_iSectors) * itemsDrawn;
				glNormal3f((vec_2.x + vec_1.x) / 2.f, 0, (vec_2.y + vec_1.y) / 2.f);
				glTexCoord2f(0.f, 1.f + 1.f * cosf(temp));
				glVertex3f(vec_1.x, slant*2 - (slant * (1.0 - vec_1.x / m_fRadius)), vec_1.y);
				glTexCoord2f(0.f, 0.f);
				glVertex3f(vec_1.x, 0, vec_1.y);
				glTexCoord2f(1.f, 0.f);
				glVertex3f(vec_2.x, 0, vec_2.y);
				glTexCoord2f(1.f, 1.f + 1.f * cosf(currentPointAngle));
				glVertex3f(vec_2.x, slant*2 - (slant * (1.0 - vec_2.x / m_fRadius)), vec_2.y);
			}
			else {
				point++;
			}
		}
		glEnd();
	}




	void generatePointList() {
		m_lPoints.clear();
		m_lPoints.push_back(glm::vec2(m_fRadius, 0.f));
		for (int i = 1; i != m_iSectors; i++) {

			float currentPointAngle = (2 * M_PI / m_iSectors) * i;
			m_lPoints.push_back(glm::vec2(m_fRadius * cosf(currentPointAngle), m_fRadius * sinf(currentPointAngle)));
		}
		m_lPoints.push_back(glm::vec2(m_fRadius, 0.f));
	}
};

