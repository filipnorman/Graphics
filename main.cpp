#include <iostream>
#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "loadimage.h"


int main()
{
    if (!glfwInit())
    {
        std::cout << "GLFW initialisation failed." << std::endl; return -1; 
    }   

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    /* For macOS uncomment the following line */
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
///    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow* window = glfwCreateWindow(512, 512, "Hello Sprite", NULL, NULL); if (!window)
    {
        std::cout << "GLFW failed to create window." << std::endl; glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glClearColor(0.f, 0.f, 0.f, 1.0f);

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        std::cout << "GLEW initialisation failed: " << glewGetErrorString(err) << std::endl;
        return -1;
    }


    GLuint tex = loadimage("ghost-vanish.bmp");

    struct UV
    {
        float ux, uy, vx, vy;
    };

    //Pre calculated sprite uvs
    UV sprite_uvs[16] =
    {
        /*U V*/
        {0.000000, 0.000000, 0.142857, 1.000000},
        {0.142857, 0.000000, 0.285714, 1.000000},
        {0.285714, 0.000000, 0.428571, 1.000000},
        {0.428571, 0.000000, 0.571429, 1.000000},
        {0.571429, 0.000000, 0.714286, 1.000000},
        {0.714286, 0.000000, 0.857143, 1.000000},
        {0.857143, 0.000000, 1.000000, 1.000000}


    };

    const int num_uvs = 7;
    int frame = 0;
    int anim_frame = 0;
    const int anim_speed = 10;

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

    	glEnable(GL_TEXTURE_2D);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    	glBindTexture(GL_TEXTURE_2D, tex);

        frame++;
        if (frame % anim_speed == 0)
        {
            anim_frame = anim_frame == 0 ? anim_frame = 6 : anim_frame - 1;
        }
        UV uv = sprite_uvs[anim_frame];

        glBegin(GL_TRIANGLES);
            glColor3f(1.0f, 1.0f, 1.0f);
            glTexCoord2f(uv.vx, uv.vy);
            glVertex3f(.5f, .5f, 0.0f);
            glTexCoord2f(uv.vx, uv.uy);
            glVertex3f(.5f, -.5f, 0.0f);
            glTexCoord2f(uv.ux, uv.uy);
            glVertex3f(-.5f, -.5f, 0.0f);
            
            glTexCoord2f(uv.ux, uv.uy);
            glVertex3f(-.5f, -.5f, 0.0f);
            glTexCoord2f(uv.ux, uv.vy);
            glVertex3f(-.5f, .5f, 0.0f);
            glTexCoord2f(uv.vx, uv.vy);
            glVertex3f(.5f, .5f, 0.0f);

        glEnd();
    	glDisable(GL_TEXTURE_2D);   
    
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}