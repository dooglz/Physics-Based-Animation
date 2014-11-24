#include <stdio.h>
#include "Game.h"
#include "Engine/engine.h"
#include "Engine/time.h"
#include "Engine/Physics_interface.h"
#include <stdint.h>
Game* GAME;
extern int culledObjects;
extern int renderedObjects;
bool demoMode = false;

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
	unsigned int loops= 0;
	while (Engine::Engine::Run() && GAME->Run())
	{
		if (!demoMode)
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
				t += physicsTimeStep;
				tt = Engine::Time::getTime();
				if ((tt - newTime) > (0.005 / tartgettime)){
					//printf("Physics stall\n");
					break;
				}
			}

			//Engine Logic update
			Engine::Engine::Update(deltaPercent);
			//Game Logic Update
			GAME->Update(deltaPercent);

			//Render
			culledObjects = 0;
			renderedObjects = 0;
			Engine::Engine::Render();
			//	printf("%i\t%i\n", culledObjects, renderedObjects);
		}
		else
		{
			unsigned int ticks = 0;
			double ff = ((1.0 / tartgettime) / physicsTimeStep);
			while (ticks < ff)
			{
				ticks++;
				Engine::PhysicsSolver->Tick(t, physicsTimeStep);
			}
			loops++;
			//Engine Logic update
			Engine::Engine::Update((1.0 / physicsTimeStep));
			//Game Logic Update
			GAME->Update((1.0 / physicsTimeStep));
			//Render
			Engine::Engine::Render();
			char buffer[50];
			
			printf(buffer, "output_%d.bmp", loops);
			std::string ss = std::string(buffer);
			ss = "output_" + std::to_string(loops)+ ".bmp";
			Engine::Engine::SaveFile(ss);
		}
	}
	
	printf("Program Quitting\n");

	GAME->Shutdown();
	delete GAME;

	printf("Bye!\n");
	return 0;
}
