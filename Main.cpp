#pragma once
#include "Graph.h"
#include <iostream>
#include <stdio.h>
#include <GL/glew.h>
#include <gl/wglew.h>
#include <GLFW\glfw3.h>
#include <fstream>
#include <time.h>
#include "texture.h"
#include "Text.h"
#include "Sprite.h"
#include "Shape.h"
#include "Game.h"

#include "Flock.h"

using namespace std;
GLuint CreateProgram(const char *a_vertex, const char *a_frag);

const int SCREEN_HEIGHT = 480;
const int SCREEN_WIDTH = 640;


int main(int argc, char ** argv)
{
	//Initialise GLFW
	if (!glfwInit())
	{
		return -1;
	}

	GLFWwindow* window;
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Flocking Demo", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -2;
	}


	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK)
	{
		// OpenGL didn't start-up! shutdown GLFW and return an error code
		glfwTerminate();
		return -3;
	}

	Text font = Text("NLuceGameEngine/fonts/font.png");

	//create shader program
	//	GLuint uiProgramFlat = CreateProgram("VertexPositionColorUV.glsl.glsl", "FlatFragmentShader.glsl");
	GLuint uiProgramColorTexture = CreateProgram("Shaders/VertexPositionColorUV.glsl", "Shaders/TexturedFragmentShader.glsl");
	//	GLuint uiProgramTexture = CreateProgram("VertexPositionUV.glsl", "FragmentPositionUV.glsl");

	//find the position of the matrix variable in the shader so we can send info there later
	GLuint shaderIDMVP = glGetUniformLocation(uiProgramColorTexture, "MVP");

	// screen is with origin at lower left (y is up)
	mat4 screen = glm::ortho(0.0f, (float)SCREEN_WIDTH, 0.0f, (float)SCREEN_HEIGHT);

	float centerX = SCREEN_WIDTH / 2;
	float centerY = SCREEN_HEIGHT / 2;

	// screenCentered is with origin at center (y is up)
	mat4 screenCentered = glm::ortho(-centerX, centerX, -centerY, centerY);

	// screenCenteredx2 is centered and scaled up by 2
	mat4 screenCenteredx2 = scale(screenCentered, vec3(2, 2, 1));

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	mat4 world = screen;

	Sprite::defaultMatrix = &world;
	Sprite::defaultMatrixLocation = shaderIDMVP;
	//	world = translate(world, vec3(centerX, centerY, 0)); // center on screen
	//	world = scale(world, vec3(gameScale, gameScale, 1.0)); // scale to screen
	//	world = translate(world, vec3(0, -cameraHeight, 0)); // vertical scrolling

	Flock flock;

	/*    GAME LOOP      */

	while (!glfwWindowShouldClose(window))
	{
		theGame.startFrame();
		{
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			glUseProgram(uiProgramColorTexture);

			flock.move(theGame.elapsedTime);
			flock.draw();

			glfwSwapBuffers(window);
		}

		//poll for and process events
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}


GLuint CreateShader(GLenum a_eShaderType, const char *a_strShaderFile)
{
	std::string strShaderCode;
	//open shader file
	std::ifstream shaderStream(a_strShaderFile);
	//if that worked ok, load file line by line
	if (shaderStream.is_open())
	{
		std::string Line = "";
		while (std::getline(shaderStream, Line))
		{
			strShaderCode += "\n" + Line;
		}
		shaderStream.close();
	}

	//convert to cstring
	char const *szShaderSourcePointer = strShaderCode.c_str();

	//create shader ID
	GLuint uiShader = glCreateShader(a_eShaderType);
	//load source code
	glShaderSource(uiShader, 1, &szShaderSourcePointer, NULL);

	//compile shader
	glCompileShader(uiShader);

	//check for compilation errors and output them
	GLint iStatus;
	glGetShaderiv(uiShader, GL_COMPILE_STATUS, &iStatus);
	if (iStatus == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(uiShader, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(uiShader, infoLogLength, NULL, strInfoLog);

		const char *strShaderType = NULL;
		switch (a_eShaderType)
		{
		case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
		case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
		}

		fprintf(stderr, "Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
		delete[] strInfoLog;
	}

	return uiShader;
}

GLuint CreateProgram(const char *a_vertex, const char *a_frag)
{
	std::vector<GLuint> shaderList;

	shaderList.push_back(CreateShader(GL_VERTEX_SHADER, a_vertex));
	shaderList.push_back(CreateShader(GL_FRAGMENT_SHADER, a_frag));

	//create shader program ID
	GLuint uiProgram = glCreateProgram();

	//attach shaders
	for (auto shader = shaderList.begin(); shader != shaderList.end(); shader++)
		glAttachShader(uiProgram, *shader);

	//link program
	glLinkProgram(uiProgram);

	//check for link errors and output them
	GLint status;
	glGetProgramiv(uiProgram, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(uiProgram, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(uiProgram, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}

	for (auto shader = shaderList.begin(); shader != shaderList.end(); shader++)
	{
		glDetachShader(uiProgram, *shader);
		glDeleteShader(*shader);
	}

	return uiProgram;
}