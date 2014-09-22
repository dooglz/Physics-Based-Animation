/*
Uncomplicated IK Simulation Tutorial

Minimilistic sample program - for educational purposes - it should
be straightforward to follow through, dissect and understand, so that you are
able to expand and incorporate the solution into your own program

www.napier.ac.uk/games/

b.kenwright@napier.ac.uk
*/

#include "windows.h"
#include "glut/glut.h"
#include "sdl/SDL.h"
#include "utilities.h"
#include "iksample.h"
#include "glut_renderer.h"

#define FPS_SAMPLE_SIZE 10

CIkSystem Isystem;
CGLut_Renderer Renderer;
void render(void);

static uint16_t previoustime;
static uint16_t times[FPS_SAMPLE_SIZE];
static uint8_t framecount;

// Program Entry Point
int main(int argc, char *argv[])
{
	Isystem.Setup();

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Simulation");

	SDL_Init(SDL_INIT_VIDEO);
	//Use OpenGL 3.1 core
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	//Create an ogl window
	SDL_Window* _window = SDL_CreateWindow("SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	// register callbacks
	glutDisplayFunc(render);
	glutIdleFunc(render);
	// enter GLUT event processing cycle
	glutMainLoop();
	return 0;
}


//Returns Delta
static uint16_t CalculateFps()
{
	const uint16_t time = glutGet(GLUT_ELAPSED_TIME);
	const uint16_t delta = time - previoustime;
	previoustime = time;
	times[framecount] = delta;
	framecount = (((framecount + 1) + FPS_SAMPLE_SIZE) % FPS_SAMPLE_SIZE);
	if (framecount == 0)
	{
		printf("FPS: %i\n", delta);
	}
	return delta;
}

void render(void)
{
	const uint16_t delta = CalculateFps();
	Renderer.PrepForRender();
	Isystem.Render();
	Renderer.FinishRender();
}

