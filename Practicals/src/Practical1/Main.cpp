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

CIkSystem Isystem;
void render(void);

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

void render(void)
{
	Isystem.Render();
}