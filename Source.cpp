#include<iostream>

#define GLEW_STATIC
#define _USE_MATH_DEFINES
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <list>
#include "math.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp> 
#include "Player.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "loadimage.h"
#include "CityGroundTiles.h"
#include "TrafficLight.h"
#include "Car.h"
#include "Buildings.h"
#include "Person.h"


GLFWwindow* window = NULL;
const char* WINDOW_TITLE = "GRA_Task2a";
const GLint WINDOW_WIDTH = 1000;
const GLint WINDOW_HEIGHT = 1000;

struct UV
{
	float ux, uy, vx, vy;
};

//UV positions for the first cube faces
UV sprite_uvs[20] =
{
	/*U V*/
	{0.000000, 0.333333, 0.250000, 0.666666},
	{0.250000, 0.333333, 0.500000, 0.666666},
	{0.500000, 0.333333, 0.750000, 0.666666},
	{0.750000, 0.333333, 1.000000, 0.666666},
	{0.250000, 0.000000, 0.500000, 0.333333},
	{0.250000, 0.666666, 0.500000, 1.000000},
};

bool initOpenGL();
void drawSolidCube(float x, float y, float z, glm::vec4 colour);
void drawSkybox(float r);

//camera stuff
bool wKey, sKey, aKey, dKey; 
bool player1turn = true;
double mouseX, mouseY;

float sensitivity = 0.01f;
float cubeSpeed = 0.05f;
void moveAndRotatePlayer(Player* player, int playerNum);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);


static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

int main() {
	std::cout << "GRA_Coursework" << std::endl;

	if (!initOpenGL())
	{
		std::cerr << "GLFW initialisation failed." << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);

	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	//Global Ambient Light
	GLfloat global_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

	

	//Global Light Source Sun
	float ambient_0[] = { 0.8f, 0.8f, 0.8f, 1.0f };      // ambient light (80% white)
	float diffuse_0[] = { 0.7f, 0.7f, 0.7f, 1.0f };      // diffuse light (70% white)
	float specular_0[] = { 1.0f, 1.0f, 1.0f, 1.0f };      // specular light (100% white)

	// Attach properties to single light source (GL_LIGHT0)
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_0);      // set ambient parameter of light source
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_0);      // set diffuse parameter of light source
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular_0);    // set specular parameter of light source

	// Enable this lighting effects
	glEnable(GL_LIGHT0);    // enable light source with attached parameters (GL_LIGHT0)

	//Car Lamp
	float ambient_1[] = { 2.f, 2.f, 2.f, 1.0f };      
	float diffuse_1[] = { 1.f, 1.f,0.f, 1.0f };      
	float specular_1[] = { 1.0f, 1.0f, 1.0f, 1.0f };     

	// Attach properties to single light source (GL_LIGHT1)
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient_1);     
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse_1);     
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular_1);   


	GLfloat spot_dir_1[] = { 0.f, 0.f, -1.f };
	GLfloat spot_cutoff_1 = 90.0f;
	GLfloat spot_exponent_1 = 16.f;
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_dir_1);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spot_cutoff_1);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, spot_exponent_1);

	// Enable this lighting effects
	glEnable(GL_LIGHT1);    // enable light source with attached parameters (GL_LIGHT1)





	glClearColor(0.4f, 0.5f, 0.6f, 1.0f);

	//player cube and eye variables
	float cubeSize = 0.2f;
	//This initialises the player code
	Player player1 = Player(glm::vec3(0.0f, 2.f, -2.f), glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 1.f, 0.f), glm::vec4(0.f,0.f,1.f,1.f));

	
	/*Inital mouse setup -> This initially only effects player 1 as that is the first turn. 
	*/
	glfwSetCursorPos(window, (WINDOW_WIDTH / 2 ) / 2, WINDOW_HEIGHT / 2 );
	
	glfwGetCursorPos(window, &mouseX, &mouseY);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	//Load textures and set up objects
	CityGroundTiles ground = CityGroundTiles();
	GLuint tex = loadimage("skyboxForCW.bmp");
	GLuint city_tex = loadimage("CityRoadText.bmp");
	GLuint glass = loadimage("glass.bmp");
	GLuint car = loadimage("carText.bmp");
	Buildings builder = Buildings();


	TrafficLight tl = TrafficLight();
	Car car1 = Car(&glass, &car, glm::vec3(-0.8f, 0.0f, -3.4f), 0, 0,1);
	Car car2 = Car(&glass, &car, glm::vec3(0.8f, 0.0f, 3.4f), 1, 2, 2);

	Person person = Person();

	//Main Loop
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		glMatrixMode(GL_PROJECTION);    // switch from model/view to projection mode    
		glLoadIdentity();               // reset matrix


		
		float aspectRatio = static_cast<GLdouble>(WINDOW_WIDTH) / static_cast<GLdouble>(WINDOW_HEIGHT);
		float znear1 = 0.1f;
		float zfar1 = 1500.f;
		float fovyInDegrees1 = 60.f;

		glm::mat4 proj1 = glm::perspective(glm::radians(fovyInDegrees1), aspectRatio, znear1, zfar1);

		float* matProjectionArray1 = glm::value_ptr(proj1);

		glLoadMatrixf(matProjectionArray1);
		
		glMatrixMode(GL_MODELVIEW);
		
		glLoadIdentity();
		//The Light source from the sun is placed so that it coressponds with the sun in the skybox
		float position_0[] = { -10.f, 10.f, 10.f, 0.f };      // directional light (w = 0)
		glLightfv(GL_LIGHT0, GL_POSITION, position_0);    // set direction vector of light source


		

		//Player 1 Camera 
		player1.eye_pos = player1.pos;
		glm::vec3 cameraDirection1 = glm::normalize(player1.direction);
		glm::vec3 up1 = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 cameraRight1 = glm::normalize(glm::cross(up1, cameraDirection1));
		glm::vec3 cameraUp1 = glm::cross(cameraDirection1, cameraRight1);
		glm::mat4 viewPlayer1 = glm::mat4(
			cameraRight1[0], cameraUp1[0], -cameraDirection1[0], 0.0f,
			cameraRight1[1], cameraUp1[1], -cameraDirection1[1], 0.0f,
			cameraRight1[2], cameraUp1[2], -cameraDirection1[2], 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
		viewPlayer1 = glm::translate(viewPlayer1, -player1.eye_pos);

		glLoadMatrixf(glm::value_ptr(viewPlayer1));

		//Building 1 Round Glass Building
		glPushMatrix();
		glTranslatef(-6.f, 0.f, -6.f); 
		builder.drawBuilding1();
		glPopMatrix();

		//Building 2 Stacked Tallest

		glPushMatrix();
		glTranslatef(6.f, 0.f, -6.f);
		builder.drawBuilding2();
		glPushMatrix();
		glTranslatef(-2.f, 0.f, 2.f);
		builder.drawBuilding3();
		glTranslatef(4.f, 0.f, -4.f); 
		builder.drawBuilding3();
		glTranslatef(-2.f, 0.f, 2.f); 
		glTranslatef(-2.f, 0.f, -2.f);
		builder.drawBuilding3();
		glTranslatef(4.f, 0.f, 4.f); 
		builder.drawBuilding3();
		glPopMatrix();
		glPopMatrix();
		moveAndRotatePlayer(&player1, 1);

		//Building 3 Brick Tower
		glPushMatrix();
		glTranslatef(-4.f, 0.f, 4.f); 
		builder.drawBuilding3();
		glPushMatrix();
		glTranslatef(-2.f, 0.f, 2.f); 
		builder.drawBuilding3();
		glTranslatef(-2.f, 0.f, 2.f); 
		builder.drawBuilding3();
		glPopMatrix();
		glTranslatef(-2.f, 0.f, 2.f); 
		glTranslatef(-2.f, 0.f, -2.f);
		builder.drawBuilding3();
		glTranslatef(4.f, 0.f, 4.f);
		builder.drawBuilding3();
		glPopMatrix();
		
		//Building 4 Hospital
		glPushMatrix();
		glTranslatef(6.f, 2.f, 6.f); 
		builder.drawBuilding4();
		glPopMatrix();

		//Traffic Light
		glPushMatrix();
		glTranslatef(1.5f, 0.f, 1.5f);
		tl.draw();

		glPopMatrix();
		glPushMatrix();
		glTranslatef(-1.5f, 0.f, -1.5f);
		glRotatef(180.f, 0.f, 1.f, 0.f);
		tl.draw();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-1.5f, 0.f, 1.5f);
		glRotatef(270.f, 0.f, 1.f, 0.f);
		tl.draw();

		glPopMatrix();
		glPushMatrix();
		glTranslatef(1.5f, 0.f, -1.5f);
		glRotatef(90.f, 0.f, 1.f, 0.f);
		tl.draw();
		glPopMatrix();

		//Spawn Cars - Cars are animated within
		glPushMatrix();
		glTranslatef(car1.location[0], car1.location[1],car1.location[2]);
		glRotatef(car1.rotation, 0.f, 1.f, 0.f);
		car1.drawCar();
		car1.checkIfStop(player1.eye_pos);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(car2.location[0], car2.location[1], car2.location[2]);
		glRotatef(car2.rotation, 0.f, 1.f, 0.f);
		car2.drawCar();
		car2.checkIfStop(player1.eye_pos);
		glPopMatrix();
		
		glPushMatrix();
		glTranslatef(person.location[0], person.location[1], person.location[2]);
		person.draw();
		//Check if the cars need to be stoped
		car1.checkIfStop(person.location);
		car2.checkIfStop(person.location);
		glPopMatrix();


        //SKYBOX 
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		glBindTexture(GL_TEXTURE_2D, tex);
		drawSkybox(750.f);
		glDisable(GL_TEXTURE_2D);

		//Ground Texture
		ground.drawGround(&city_tex);
			
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}


//This moves and rotates the player.
void moveAndRotatePlayer(Player* player, int playerNum) {

	//Sets up the player rotation
	(*player).direction = glm::normalize((*player).head);
	(*player).right = glm::normalize( glm::cross( glm::vec3(0.f,1.f,0.f), (*player).direction));
	(*player).up = glm::cross( (*player).direction, (*player).right);

	(*player).rotation = glm::mat4(
		-(*player).right[0], -(*player).right[1], -(*player).right[2], 0.0f,
		(*player).up[0], (*player).up[1], (*player).up[2], 0.0f,
		-(*player).direction[0], -(*player).direction[1], -(*player).direction[2], 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	(*player).head = (*player).head + (*player).right * (float)((xpos - mouseX) * sensitivity);
	(*player).head = (*player).head + (*player).up * (float)(-(ypos - mouseY) * sensitivity);

	mouseX = xpos;
	mouseY = ypos;


	if (wKey)
	{
		(*player).pos = (*player).pos + (*player).direction * cubeSpeed;
	}

	if (sKey)
	{
		(*player).pos = (*player).pos + (*player).direction * -cubeSpeed;
	}

	if (aKey)
	{
		(*player).pos = (*player).pos + (*player).right * -cubeSpeed;
	}
	if (dKey)
	{
		(*player).pos = (*player).pos + (*player).right * cubeSpeed;
	}
}

//Keyboard imput -> 1/2 to change player contollers respectively | WASD - Move | Mouse - Camera  
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		std::cout << "Esc key is pressed." << std::endl;
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		wKey = true;
	}

	if (key == GLFW_KEY_W && action == GLFW_RELEASE)
	{
		wKey = false;
	}

	if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		sKey = true;
	}

	if (key == GLFW_KEY_S && action == GLFW_RELEASE)
	{
		sKey = false;
	}

	if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		aKey = true;
	}

	if (key == GLFW_KEY_A && action == GLFW_RELEASE)
	{
		aKey = false;
	}

	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		dKey = true;
	}

	if (key == GLFW_KEY_D && action == GLFW_RELEASE)
	{
		dKey = false;
	}

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		glLoadIdentity();
	}
	
}


bool initOpenGL()
{
	/* Initialize the GLFW library */
	if (!glfwInit()) {
		std::cout << "GLFW initialisation failed." << std::endl;
		return false;
	}

	glfwSetErrorCallback(error_callback);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
	if (!window)
	{
		std::cout << "GLFW failed to create window." << std::endl;
		glfwTerminate();
		return false;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);

	/* Initialize the GLEW library */
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		/* Problem: glewInit failed, something is seriously wrong */
		std::cout << "GLEW initialisation failed: " << glewGetErrorString(err) << std::endl;
		return false;
	}
	std::cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;

	return true;
}

void drawSkybox(float r)
{
	glBegin(GL_QUADS);

	UV uv = sprite_uvs[3];
	//Cube made out of triangles
	//Back Face 
	glNormal3f(0.f, 0.f, -1.f);
	glTexCoord2f(uv.vx, uv.uy);
	glVertex3f(r, -r, r);
	glTexCoord2f(uv.vx, uv.vy);
	glVertex3f(r, r, r);
	glTexCoord2f(uv.ux, uv.vy);
	glVertex3f(-r, r, r);
	glTexCoord2f(uv.ux, uv.uy);
	glVertex3f(-r, -r, r);

	// Front face
	uv = sprite_uvs[1];
	glNormal3f(0.f, 0.f, 1.f);
	glTexCoord2f(uv.ux, uv.uy);
	glVertex3f(r, -r, -r);
	glTexCoord2f(uv.vx, uv.uy);
	glVertex3f(-r, -r, -r);
	glTexCoord2f(uv.vx, uv.vy);
	glVertex3f(-r, r, -r);
	glTexCoord2f(uv.ux, uv.vy);
	glVertex3f(r, r, -r);

	// Right face
	uv = sprite_uvs[0];
	glTexCoord2f(uv.vx, uv.uy);
	glNormal3f(-1.f, 0.f, 0.f);
	glVertex3f(r, -r, -r);
	glTexCoord2f(uv.vx, uv.vy);
	glVertex3f(r, r, -r);
	glTexCoord2f(uv.ux, uv.vy);
	glVertex3f(r, r, r);
	glTexCoord2f(uv.ux, uv.uy);
	glVertex3f(r, -r, r);


	// Left face
	uv = sprite_uvs[2];
	glNormal3f(1.f, 0.f, 0.f);
	glTexCoord2f(uv.ux, uv.uy);
	glVertex3f(-r, -r, -r);
	glTexCoord2f(uv.vx, uv.uy);
	glVertex3f(-r, -r, r);
	glTexCoord2f(uv.vx, uv.vy);
	glVertex3f(-r, r, r);
	glTexCoord2f(uv.ux, uv.vy);
	glVertex3f(-r, r, -r);

	// Bottom face
	uv = sprite_uvs[4];
	glNormal3f(0.f, -1.f, 0.f);
	glTexCoord2f(uv.ux, uv.vy);
	glVertex3f(-r, -r, -r);
	glTexCoord2f(uv.ux, uv.uy);
	glVertex3f(r, -r, -r);
	glTexCoord2f(uv.vx, uv.uy);
	glVertex3f(r, -r, r);
	glTexCoord2f(uv.vx, uv.vy);
	glVertex3f(-r, -r, r);


	// Top face
	uv = sprite_uvs[5];
	glNormal3f(0.f, 1.f, 0.f);
	glTexCoord2f(uv.vx, uv.uy);
	glVertex3f(-r, r, -r);
	glTexCoord2f(uv.vx, uv.vy);
	glVertex3f(-r, r, r);
	glTexCoord2f(uv.ux, uv.vy);
	glVertex3f(r, r, r);
	glTexCoord2f(uv.ux, uv.uy);
	glVertex3f(r, r, -r);

	glEnd();
	
}

void drawSolidCube(float x, float y, float z, glm::vec4 colour) 
{
	// Material properties
	/*
	glPushAttrib(GL_ALL_ATTRIB_BITS); // save current style attributes (inc. material properties)

	float mat_ambient[] = { 0.5f, 0.5f, 0.5f, 1.f };	// ambient colour
	float mat_diffuse[] = { 0.5f, 0.5f, 0.5f, 1.f };	// colour reflected by diffuse light
	float mat_specular[] = { 0.f, 0.f, 0.f, 1.f };		// specular colour
	float mat_shininess[] = { 0.0f }; // [0, 128]
	float mat_emission[] = { 0.f, 0.f, 0.f, 1.f };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);	// set colour for ambient reflectance
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);	// set colour for diffuse reflectance
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);	// set colour for specular reflectance
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	*/
	glColor4f(colour[0], colour[1], colour[2], colour[3]);
	glBegin(GL_QUADS);

	// Back face (z = r)

	glNormal3f(0.f, 0.f, 1.f);
	glTexCoord2f(1.f, 1.f);
	glVertex3f(x, y, z);
	glTexCoord2f(1.f, 0.f);
	glVertex3f(x, -y, z);
	glTexCoord2f(0.f, 0.f);
	glVertex3f(-x, -y, z);
	glTexCoord2f(0.f, 1.f);
	glVertex3f(-x, y, z);

	// Near face (z = -r)

	glNormal3f(0.f, 0.f, -1.f);
	glTexCoord2f(1.f, 1.f);
	glVertex3f(x, y, -z);
	glTexCoord2f(0.f, 1.f);
	glVertex3f(-x, y, -z);
	glTexCoord2f(0.f, 0.f);
	glVertex3f(-x, -y, -z);
	glTexCoord2f(1.f, 0.f);
	glVertex3f(x, -y, -z);

	// Right face (x = r)

	glNormal3f(1.f, 0.f, 0.f);
	glTexCoord2f(1.f, 1.f);
	glVertex3f(x, y, z);
	glTexCoord2f(1.f, 0.f);
	glVertex3f(x, y, -z);
	glTexCoord2f(0.f, 0.f);
	glVertex3f(x, -y, -z);
	glTexCoord2f(0.f, 1.f);
	glVertex3f(x, -y, z);

	// Left face (x = -r)

	glNormal3f(-1.f, 0.f, 0.f);
	glTexCoord2f(1.f, 1.f);
	glVertex3f(-x, y, z);
	glTexCoord2f(0.f, 1.f);
	glVertex3f(-x, -y, z);
	glTexCoord2f(0.f, 0.f);
	glVertex3f(-x, -y, -z);
	glTexCoord2f(0.f, 0.f);
	glVertex3f(-x, y, -z);

	// Top face (y = r)

	glNormal3f(0.f, 1.f, 0.f);
	glVertex3f(x, y, z);
	glVertex3f(-x, y, z);
	glVertex3f(-x, y, -z);
	glVertex3f(x, y, -z);

	// Bottom face (y = -r)

	glNormal3f(0.f, -1.f, 0.f);
	glVertex3f(x, -y, z);
	glVertex3f(x, -y, -z);
	glVertex3f(-x, -y, -z);
	glVertex3f(-x, -y, z);

	glEnd();
	//glPopAttrib(); // restore style attributes
}
