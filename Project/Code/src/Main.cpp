#include <stdio.h>
#include "Game.h"
#include "Engine/engine.h"
#include "Engine/time.h"
#include "Engine/Physics.h"

Game* GAME;

int main(int argc, char** argv)
{
	//Code Start
	GAME = new Game();
	
	GAME->Init();

	//Variables for timestep and delta calculations
	double t = 0.0;
	const double physicsTimeStep = 0.00001;
	unsigned long currentTime = Engine::Time::getTime();
	double accumulator = 0.0;

	//Begin loop
	while (Engine::Engine::Run() && GAME->Run())
	{
		unsigned long newTime = Engine::Time::getTime();
		double delta = newTime - currentTime;
		currentTime = newTime;
		
		//Physics
		/*
		accumulator += delta;
		while (accumulator >= physicsTimeStep)
		{

			Engine::Physics::Tick(t, physicsTimeStep);
			accumulator -= physicsTimeStep;
			t += physicsTimeStep;
		}
		*/

		//Engine Logic update
		Engine::Engine::Update(delta);
		//Game Logic Update
		GAME->Update(delta);

		//Render
		Engine::Engine::Render();
	}

	printf("Program Quitting\n");

	GAME->Shutdown();
	delete GAME;

	printf("Bye!\n");
	return 0;
}