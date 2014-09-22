/*
Uncomplicated IK Simulation Tutorial

Minimilistic sample program - for educational purposes - it should
be straightforward to follow through, dissect and understand, so that you are
able to expand and incorporate the solution into your own program

www.napier.ac.uk/games/

b.kenwright@napier.ac.uk
*/
#include "glew/glew.h"
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
void GLInfo()
{
	printf("---------------- OpenGL Info -----------------------------------\n");
	printf("    Version: %s\n", glGetString(GL_VERSION));
	printf("     Vendor: %s\n", glGetString(GL_VENDOR));
	printf("   Renderer: %s\n", glGetString(GL_RENDERER));
	printf("    Shading: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	printf("----------------------------------------------------------------\n");
}

void init(){

}


// Program Entry Point
int main(int argc, char *argv[])
{
	init();
	Isystem.Setup();

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Simulation");

	SDLVersionInfo();
	SDL_Init(SDL_INIT_VIDEO);
	SDL_SetAssertionHandler(CustomAssertionHandler, NULL);

	//Use OpenGL 3.1 core
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	//Create an ogl window
	SDL_Window* _window = SDL_CreateWindow("SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	//Create context
	SDL_GLContext _gContext = SDL_GL_CreateContext(_window);
	SDL_assert(_gContext != NULL);
	GLInfo();

	//Initialize GLEW, do we even need it?
	glewExperimental = GL_TRUE;
	SDL_assert(glewInit() == GLEW_OK);
	//Glewinit always throws an error, due to that experimental flag, just ignore it.
	glGetError();

	//Use Vsync
	SDL_assert(SDL_GL_SetSwapInterval(1) >= 0);
	

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
	//	printf("FPS: %i\n", delta);
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

