#pragma once
#include <math.h>
#include <iostream>
#include <list>

//Helper classes for sub surface division variables.
class Point {
public:
	Point(float _x1, float _y1, float _z1)
		: x(_x1)
		, y(_y1)
		, z(_z1)
	{

	}

	Point& operator=(const Point& pt)
	{
		x = pt.x;
		y = pt.y;
		z = pt.z;
		return *this;
	}

	void PushOut(float radius) {
		float ratio = sqrtf(pow(radius, 2) / (powf(x, 2) + powf(y, 2) + powf(z, 2)));

		x = x * ratio;
		y = y * ratio;
		z = z * ratio;


	}


public:
	float x;
	float y;
	float z;

};

//Triangle Class helps find the midpoints of a triangle.
class Triangle {

public:

	Triangle(Point _A, Point _B, Point _C)
		: A(_A)
		, B(_B)
		, C(_C)	
	{

	}

	~Triangle() {

		
		
	}

	std::list<Triangle*>* subDivide(float r) {

		Point AB = MidPoint(A, B);
		Point BC = MidPoint(B, C);
		Point CA = MidPoint(C, A);

		AB.PushOut(r);
		BC.PushOut(r);
		CA.PushOut(r);

		std::list<Triangle*>* triangles = new std::list<Triangle*>();
		triangles->push_back( new Triangle(A, AB, CA));   //TOP
		triangles->push_back( new Triangle(C, CA, BC));   //LEFT
		triangles->push_back( new Triangle(CA, AB, BC));  //MID
		triangles->push_back( new Triangle(B, BC, AB));   //RIGHT

		return triangles;

	}

	Point MidPoint(Point a, Point b) {

		return Point((a.x + b.x)/2, (a.y + b.y)/2, (a.z + b.z)/2);


	}



public:
	Point A;
	Point B;
	Point C;
	bool blue;


};


