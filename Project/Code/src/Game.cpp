#include "Game.h"
#include "Engine/engine.h"
#include "Engine/Scene.h"
#include "Engine/Input.h"
#include "Engine/Cm_MeshRenderer.h"
#include "Engine/Cm_Camera.h"
#include "Engine/Cm_Physics.h"
#include "Engine/Renderer.h"
#include "Cm_FpsMotor.h"

#include <stdio.h>

Engine::Entity* ent1;
Engine::Entity* ent2;
Engine::Entity* ent3;
float a = 0.0f;

void Game::registerInputs()
{
	//Todo: read these from file
	//using pushback rather than a={...} as the ps3 compiler is old and dumb
	std::vector<std::string> a;

	a.push_back("kb_space"); a.push_back("gp_1_start"); a.push_back("ms_l");
	Engine::Input::addMap("action1", a);
	a.clear();
}

Game::Game(){
	printf("Project for Physics Based Animation\n(SET09119) Edinburgh Napier University\nSam Serrels\n");
}

void Game::Init(){
	Engine::Engine::Init();
	Engine::Engine::createwindow();

	ent1 = new Engine::Entity();
	ent1->SetName("Cool cube");
	ent1->setPosition(Vector3(0, 3, 0));
	ent1->AddComponent(new Engine::CmMeshRenderer());
	ent1->getComponent<Engine::CmMeshRenderer>()->setMesh("models/cube.obj");
	ent1->AddComponent(new Engine::CmPhysics_Cuboid(10,ent1->getPosition(), ent1->getScale().x, ent1->getScale().y, ent1->getScale().z));
	ent1->getComponent<Engine::CmPhysics_Cuboid>()->SetUsesGravity(true);
	Engine::ActiveScene->AddEntity(ent1);


	ent2 = new Engine::Entity();
	ent2->SetName("floor");
	ent2->setPosition(Vector3(0, -0.05, 0));
	ent2->setScale(Vector3(10, 0.1,10));
	ent2->AddComponent(new Engine::CmMeshRenderer());
	ent2->getComponent<Engine::CmMeshRenderer>()->setMesh("models/cube.obj");
	ent2->AddComponent(new Engine::CmPhysics_Plane(Vector3(0, -0.05, 0), Vector3(0, 1, 0)));
	Engine::ActiveScene->AddEntity(ent2);

	ent3 = new Engine::Entity();
	ent3->SetName("Camera");
	ent3->setPosition(Vector3(-2.8, 2.5, 2.3));
	ent3->setRotation(Vector3(-0.43f,- 0.99f, 0));
	ent3->AddComponent(new CmFpsMotor());
	ent3->AddComponent(new Engine::CmCamera());
	//Todo: do this automagically
	ent3->getComponent<Engine::CmCamera>()->Activate();
	Engine::ActiveScene->AddEntity(ent3);

	registerInputs();
}

void Game::Update(double delta)
{
	//printf("TICK: %f\n", delta*100);
	a+=(float)delta;
	if (Engine::Input::getMapData("action1") > 128){
		printf("action pressed\n");
		Engine::ActiveScene->report();
	}
	Engine::Renderer->DrawLine(Vector3(0.0f), Vector3(3 * sin(a), 3.5f, 3 * cos(a)));

	//Engine::Renderer->DrawLine(Vector3(0.0f), Vector3(-3 * sin(a), 3.5f, -3 * cos(a)));
}

void Game::Shutdown()
{
	//delete camera;
	delete ent3;
	delete ent2;
	delete ent1;
	Engine::Engine::Shutdown();
}