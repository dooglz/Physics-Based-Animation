#include <stdio.h>
#include "Game.h"
#include "Engine/engine.h"
#include "Engine/time.h"
#include "Engine/Physics_interface.h"
#include <stdint.h>
Game* GAME;
extern int coolio1;
extern int coolio2;

int main(int argc, char** argv)
{
	//Code Start
	GAME = new Game();
	
	GAME->Init();

	//Current world time in physics land
	double t = 0;
	//Physics timestep (0.01 seconds)
	double  physicsTimeStep = 0.01;
	//Current time in Microseconds.
	double currentTime = Engine::Time::getTime();
	//60fps in Microseconds.
	double tartgettime = 60;
	double accumulator = 0;

	//Begin loop
	while (Engine::Engine::Run() && GAME->Run())
	{
		double newTime = Engine::Time::getTime();
		double delta = newTime - currentTime;
		currentTime = newTime;
		// delta / 60fps
		double deltaPercent = (double)delta / (double)tartgettime;

		//Physics
		accumulator += delta;

		double tt = 0;
		while (accumulator >= physicsTimeStep)
		{
			Engine::PhysicsSolver->Tick(t, physicsTimeStep);
			accumulator -= physicsTimeStep;
			t +=  physicsTimeStep;
			tt = Engine::Time::getTime();
			if ((tt - newTime) > (0.01 / tartgettime)){
				//printf("Physics stall\n");
				break;
			}
		}

		//Engine Logic update
		Engine::Engine::Update(deltaPercent);
		//Game Logic Update
		GAME->Update(deltaPercent);

		//Render
		coolio1 = 0;
		coolio2 = 0;
		Engine::Engine::Render();
		printf("%i\t%i\n", coolio1, coolio2);
	}
	
	printf("Program Quitting\n");

	GAME->Shutdown();
	delete GAME;

	printf("Bye!\n");
	return 0;
}
