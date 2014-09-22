/*
Uncomplicated IK Simulation Tutorial

Minimilistic sample program - for educational purposes - it should
be straightforward to follow through, dissect and understand, so that you are
able to expand and incorporate the solution into your own program

www.napier.ac.uk/games/

b.kenwright@napier.ac.uk
*/

#include "windows.h"
#include "GL/glut.h"
#include "utilities.h"
#include "iksample.h"
#include "renderer.h"

#define FPS_SAMPLE_SIZE 10

CIkSystem Isystem;
CRenderer Renderer;
void render(void);

static uint16_t previoustime;
static uint16_t times[FPS_SAMPLE_SIZE];
static uint8_t framecount;

// Program Entry Point
void main(int argc, char **argv)
{
	Isystem.Setup();

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Simulation");

	// register callbacks
	glutDisplayFunc(render);
	glutIdleFunc(render);
	// enter GLUT event processing cycle
	glutMainLoop();
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

