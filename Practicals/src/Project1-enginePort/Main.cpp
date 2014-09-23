/*
ENGINE MAIN
Sam Serrels
sam@samserrels.com
*/
#include <stdio.h>
#include "engine/GameEngine.h"
#include "ik_demo.h"

int main(int argc, char** argv)
{
	puts("Program Entry Point: Main\n");

	Engine::GameEngine::init();
	CIK_Demo * GameCode = new CIK_Demo();
	GameCode->init();

	float delta = 0;

	puts("Starting loop\n");

	unsigned int prevtime = Engine::GameEngine::getTime();
	while (Engine::GameEngine::run)
	{
		//get time in microseconds
		unsigned int time = Engine::GameEngine::getTime();

		delta = ((float)(time - prevtime)) / (1000000.0f / 60.0f);

		prevtime = time;

		//Update engine 
		Engine::GameEngine::update(delta);

		//Update game
		GameCode->update(delta);

		//Render
		Engine::GameEngine::render();
		GameCode->render();

		// Finished Drawing
		Engine::GameEngine::Postrender();
	}

	puts("Shutting Down\n");

	GameCode->shutdown();
	Engine::GameEngine::shutdown();

	delete GameCode;
	GameCode = NULL;

	puts("Quitting\n");
	return 0;
}