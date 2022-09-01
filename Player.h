#pragma once
#include<iostream>

#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <list>
#include "math.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp> 

float cubeSize = 0.5f;
glm::vec3 cube_pos = glm::vec3(0.f, 0.0f, -2.f);	// Position in World Space
glm::vec3 cube_head = glm::vec3(0.f, 0.f, 1.f);
glm::vec3 cube_fixup = glm::vec3(0.f, 1.f, 0.f);
glm::vec3 cube_up = cube_fixup;
glm::vec3 cube_direction;
glm::vec3 cube_right;
glm::mat4 cube_rotation;

//Free Mode Camera Class
class Player {
public:

	Player(glm::vec3 pos_, glm::vec3 head_, glm::vec3 up_, glm::vec4 colour_) : pos(pos_), head(head_), up(up_), colour(colour_) {

	}

	~Player() {

	}

	//player location/Orientation 
	glm::vec3 pos; 
	glm::vec3 head;
	glm::vec3 up;
	glm::vec3 direction = glm::vec3();
	glm::vec3 right =  glm::vec3();
	glm::mat4 rotation = glm::mat4();


	//player camera values
	//position of eye
	glm::vec3 eye_pos = glm::vec3(0.f,0.2f, 0.f);


	glm::vec4 colour;




};


