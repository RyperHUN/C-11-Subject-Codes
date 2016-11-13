#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ThirdParty/pugixml.hpp"
#include <iostream>

#if defined(__APPLE__)
#include <OpenGL/glew.h>
#include <OpenGL/freeglut.h>
#else
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#include <windows.h>
#endif
#include <GL/glew.h>		// must be downloaded 
#include <GL/freeglut.h>	// must be downloaded unless you have an Apple
#endif

#include "Shader.h"
#include "Rectangle.h"
#include "InputHandler.h"

const unsigned int windowWidth = 600, windowHeight = 600;

// OpenGL major and minor versions
int majorVersion = 3, minorVersion = 0;

#include "Input/GamePad.h"

Gamepad * player1Controller;
InputMapping::InputHandler* inputHandler;

void pugXmlTest()
{
	pugi::xml_document doc;

	pugi::xml_parse_result result = doc.load_file("cd_catalog.xml");

	std::cout << "Load result: " << result.description() << std::endl;

	for (auto catalog : doc.children("CATALOG"))
	{
		for (auto cd : catalog.children("CD"))
		{
			std::cout << "CD - " ;

			for (auto attr : cd.attributes ())
			{
				std::cout << " " << attr.name() << "=" << attr.value();
			}

			for (pugi::xml_node child : cd.children())
			{
				std::cout << ", child " << child.name() << "val=" << child.first_child().value();
			}
			std::cout << std::endl;
		}
	}
}
GameObject::Rectangle rect;
// Initialization, create an OpenGL context
void onInitialization() {
	glViewport(0, 0, windowWidth, windowHeight);

	player1Controller = new Gamepad (1); ///TODO Leak

	Shader * shader = new Shader ();
	shader->createShader ();

	rect.setShader (shader);
	rect.loadToGpu ();

	//pugXmlTest ();
	inputHandler = new InputMapping::InputHandler (); ///TODO LEAK
	inputHandler->handleGamepad (*player1Controller);
}



//=============================== ====================================EVENTS===================================================================================/
void onExit() {
	printf("exit");
}

// Window has become invalid: Redraw
void onDisplay() {
	glClearColor(0, 0, 0, 0);							// background color 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the screen

	rect.Draw ();

	glutSwapBuffers();									// exchange the two buffers
}


// Key  ASCII code pressed
void onKeyboard(unsigned char key, int pX, int pY) {
	if (key == 'd')
		;
}

// Key of ASCII code released
void onKeyboardUp(unsigned char key, int pX, int pY) {
	if (key == 'd')
		printf("(d RELASE) \t");
}

// Mouse click event
void onMouse(int button, int state, int pX, int pY) {
	
}

// Move mouse with key pressed
void onMouseMotion(int pX, int pY) {
}

// Idle event indicating that some time elapsed: do animation here
void onIdle() {
	long time = glutGet(GLUT_ELAPSED_TIME); // elapsed time since the start of the program
	float sec = time / 1000.0f;
	

	glutPostRedisplay();					// redraw the scene
}

int main(int argc, char * argv[]) {
	glutInit(&argc, argv);

	glutInitContextVersion(majorVersion, minorVersion);
	glutInitWindowSize(windowWidth, windowHeight);				// Application window is initially of resolution 600x600
	glutInitWindowPosition(100, 100);							// Relative location of the application window
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);  // 8 bit R,G,B,A + double buffer + depth buffer
	glutCreateWindow(argv[0]);
	glewExperimental = true;
	glewInit();

	printf("GL Vendor    : %s\n", glGetString(GL_VENDOR));
	printf("GL Renderer  : %s\n", glGetString(GL_RENDERER));
	printf("GL Version (string)  : %s\n", glGetString(GL_VERSION));
	glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
	glGetIntegerv(GL_MINOR_VERSION, &minorVersion);
	printf("GL Version (integer) : %d.%d\n", majorVersion, minorVersion);
	printf("GLSL Version : %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	onInitialization();

	glutDisplayFunc(onDisplay);                // Register event handlers
	glutMouseFunc(onMouse);
	glutIdleFunc(onIdle);
	glutKeyboardFunc(onKeyboard);
	glutSetKeyRepeat (GLUT_KEY_REPEAT_OFF); 
	glutKeyboardUpFunc(onKeyboardUp);
	glutMotionFunc(onMouseMotion);

	glutMainLoop();
	onExit();
	return 1;
}
