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
#include "ogl_renderer.h"
#include "shape_Renderer.h"
#define FPS_SAMPLE_SIZE 10


CIkSystem Isystem;
CGLut_Renderer Renderer;
COGL_Renderer ORenderer;
void render(void);

static uint16_t previoustime;
static uint16_t times[FPS_SAMPLE_SIZE];
static uint8_t framecount;

void CheckGL(){
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		printf("An OGL error has occured: %i\n", err);
		//DBG_HALT;
	}
}

void CheckSDL(){
	const char* err = SDL_GetError();
	if (strlen(err) != 0){
		printf("SDL error: %s\n", err);
		SDL_ClearError();
		//DBG_HALT;
	}
}

SDL_assert_state CustomAssertionHandler(const SDL_assert_data* data, void* userdata)
{
	CheckGL();
	CheckSDL();
	SDL_AssertionHandler defaultHandler = SDL_GetDefaultAssertionHandler();
	return defaultHandler(data, userdata);
}





void SDLVersionInfo()
{
	SDL_version compiled;
	SDL_version linked;

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	printf("Compiled against SDL version %d.%d.%d ...\n",
		compiled.major, compiled.minor, compiled.patch);
	printf("linking against SDL version %d.%d.%d.\n",
		linked.major, linked.minor, linked.patch);
}

void init(){
	SDLVersionInfo();
	SDL_Init(SDL_INIT_VIDEO);
	SDL_SetAssertionHandler(CustomAssertionHandler, NULL);
	ORenderer.InitDisplay();
}
void initGlut()
{
	// init GLUT and create window

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

// Program Entry Point
int main(int argc, char *argv[])
{
	init();
	Isystem.Setup();
	glutInit(&argc, argv);

	CShape_Renderer::Init();

	initGlut();
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
	//	printf("FPS: %i\n", delta);
	}
	return delta;
}

void render(void)
{
	ORenderer.PrepForRender();
	ORenderer.Clear();


	const uint16_t delta = CalculateFps();
	Renderer.PrepForRender();
	Isystem.Render();
	Renderer.FinishRender();

	ORenderer.FinishRender();
}

