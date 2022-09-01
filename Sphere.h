#pragma once
#include<iostream>

#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <list>
#include "math.h"
#include "sphereMath.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp> 


//Spheres using subdivision surfaces
class Sphere {
public:

	std::list<Triangle*>* triangles = NULL;
	float objectRad;

	Sphere(float r) : objectRad(r)  {
		surfaceSubdivision(r);
	}
	//Memory Management, Triangle Memory has to be freed.
	~Sphere() {
		if (triangles != NULL) {
			for (std::list<Triangle*>::iterator tri = (*triangles).begin(); tri != (*triangles).end();) {
				Triangle* tempTriangle = *tri;
				tri++;
				delete(tempTriangle);
			}
			delete(triangles);

		}
	}

	//Subdivision function. Itterates through all the triangles and calls subdivide to generate a new list of triangles. 
	void surfaceSubdivision(float r) {
		triangles = new std::list<Triangle*>();

		//Top

		triangles->push_back(new Triangle(Point(0, r, 0), Point(r, 0, 0), Point(0, 0, r)));
		triangles->push_back(new Triangle(Point(0, r, 0), Point(0, 0, r), Point(-r, 0, 0)));
		triangles->push_back(new Triangle(Point(0, r, 0), Point(-r, 0, 0), Point(0, 0, -r)));
		triangles->push_back(new Triangle(Point(0, r, 0), Point(0, 0, -r), Point(r, 0, 0)));

		//Bottom
		triangles->push_back(new Triangle(Point(0, -r, 0), Point(0, 0, r), Point(r, 0, 0)));
		triangles->push_back(new Triangle(Point(0, -r, 0), Point(-r, 0, 0), Point(0, 0, r)));
		triangles->push_back(new Triangle(Point(0, -r, 0), Point(0, 0, -r), Point(-r, 0, 0)));
		triangles->push_back(new Triangle(Point(0, -r, 0), Point(r, 0, 0), Point(0, 0, -r)));

		int iterations = 3;    //Change this variable to change the subdivision depth 
		for (int i = 0; i < iterations; i++) {
			std::list<Triangle*>* temp = new std::list<Triangle*>();


			for (std::list<Triangle*>::iterator tri = (*triangles).begin(); tri != (*triangles).end(); tri++) {
				std::list<Triangle*>* innerTemp = (*tri)->subDivide(r);
				for (std::list<Triangle*>::iterator itTri = (*innerTemp).begin(); itTri != (*innerTemp).end(); itTri++) {
					temp->push_back(*itTri);
				}
				delete(innerTemp);
			}

			Triangle* tempTriangle;
			for (std::list<Triangle*>::iterator tri = (*triangles).begin(); tri != (*triangles).end();) {
				tempTriangle = *tri;
				tri++;
				delete(tempTriangle);
			}
			delete(triangles);
			triangles = temp;
		}
	}

	//Iterates through the list of tirangles generated.
	void draw() {
		for (std::list<Triangle*>::iterator tri = (*triangles).begin(); tri != (*triangles).end(); tri++) {
			drawTriangle((**tri));
		}
	}


	//Draws triangles and works out the normals, by taking into consideration all the axis values.
	void drawTriangle(Triangle t) {
		glBegin(GL_TRIANGLES);
		glNormal3f((t.A.x + t.B.x + t.C.x) / 3.f, (t.A.y + t.B.y + t.C.y) / 3.f, (t.A.z + t.B.z + t.C.z) / 3.f);
		glVertex3f(t.A.x, t.A.y, t.A.z);
		glVertex3f(t.B.x, t.B.y, t.B.z);
		glVertex3f(t.C.x, t.C.y, t.C.z);

		glEnd();

	}



};