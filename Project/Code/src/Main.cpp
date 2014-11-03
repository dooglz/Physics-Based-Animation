#include <stdio.h>
#include "Game.h"
#include "Engine/engine.h"
#include "Engine/time.h"
#include "Engine/Physics.h"
#include <stdint.h>
Game* GAME;

int main(int argc, char** argv)
{
	//Code Start
	GAME = new Game();
	
	GAME->Init();

	//Current world time in physics land
	unsigned long t = 0;
	//Physics timestep (0.01 seconds) in Microseconds
	unsigned long  physicsTimeStep = 10000;
	//Current time in Microseconds.
	unsigned long currentTime = Engine::Time::getTime();
	//60fps in Microseconds.
	unsigned long tartgettime = 60 * 1000 * 1000;

	unsigned long accumulator = 0;

	//Begin loop
	while (Engine::Engine::Run() && GAME->Run())
	{
		unsigned long newTime = Engine::Time::getTime();
		unsigned long delta = newTime - currentTime;
		currentTime = newTime;
		// delta / 60fps
		double deltaPercent = (double)delta / (double)tartgettime;

		//Physics
		
		accumulator += delta;
		while (accumulator >= physicsTimeStep)
		{
			Engine::PhysicsSolver->Tick(t, physicsTimeStep);
			accumulator -= physicsTimeStep;
			t += physicsTimeStep;
		}
		

		//Engine Logic update
		Engine::Engine::Update(deltaPercent);
		//Game Logic Update
		GAME->Update(deltaPercent);

		//Render
		Engine::Engine::Render();
	//	printf("Time: %u\tDelta: %u,\tpercent: %e\n",newTime,delta,deltaPercent);
	}
	
	printf("Program Quitting\n");

	GAME->Shutdown();
	delete GAME;

	printf("Bye!\n");
	return 0;
}