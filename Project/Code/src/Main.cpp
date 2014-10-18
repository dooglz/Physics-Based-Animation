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
	const double physicsTimeStep = 0.01;
	double currentTime = Engine::Time::now();
	double accumulator = 0.0;

	//Begin loop
	while (Engine::Engine::Run() && GAME->Run())
	{
		double newTime = Engine::Time::now();
		double delta = newTime - currentTime;
		currentTime = newTime;

		//Physics
		accumulator += delta;
		while (accumulator >= physicsTimeStep)
		{

			Engine::Physics::Tick(t, physicsTimeStep);
			accumulator -= physicsTimeStep;
			t += physicsTimeStep;
		}
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