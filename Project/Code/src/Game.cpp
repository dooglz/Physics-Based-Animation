#include "Game.h"
#include "Engine/engine.h"
#include "Engine/Ent_Primative.h"
#include "Engine/Scene.h"
#include "Ent_FpCamera.h"
#include "Engine/Input.h"
#include "Engine/MeshRenderer.h"

#include <stdio.h>

Engine::Entity* ent1;
Engine::Entity* ent2;
EFpCamera* camera;
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
	//Engine::CmMeshRenderer *

	ent1 = new Engine::Entity();
	ent1->SetName("Cool cube");
	ent1->setPosition(Vector3(0, 1, 0));
	ent1->AddComponent(new Engine::CmMeshRenderer());
	ent1->getComponent<Engine::CmMeshRenderer>()->setMesh("models/cube.obj");
	Engine::ActiveScene->AddEntity(ent1);

	ent2 = new Engine::Entity();
	ent2->SetName("Cool cube2");
	ent2->setPosition(Vector3(0, -0.05, 0));
	ent2->setScale(Vector3(10, 0.1,10));
	ent2->AddComponent(new Engine::CmMeshRenderer());
	ent2->getComponent<Engine::CmMeshRenderer>()->setMesh("models/cube.obj");
	Engine::ActiveScene->AddEntity(ent2);

	camera = new EFpCamera();
	//Todo: do this automagically
	Engine::ActiveScene->AddEntity(camera);
	camera->Activate();

	registerInputs();
}

void Game::Update(double delta)
{
	//printf("TICK: %f\n", delta*100);
	a+=delta;
	if (Engine::Input::getMapData("action1") > 128){
		printf("action pressed\n");
	}
	
}

void Game::Shutdown()
{
	delete camera;
	delete ent1;
	Engine::Engine::Shutdown();
}