#include "Game.h"
#include "Engine/engine.h"
#include "Engine/Ent_Primative.h"
#include "Engine/Scene.h"
#include "Engine/Ent_Camera.h"
#include "Engine/Input.h"
#include <stdio.h>

Engine::Entity* ent1;
Engine::Entity* ent2;
Engine::ECamera* camera;
float a = 0.0f;

void registerInputs()
{
	//Todo: read these from file
	//using pushback rather than a={...} as the ps3 compiler is old and dumb

	std::vector<std::string> a;

	a.push_back("kb_space"); a.push_back("gp_1_start"); a.push_back("ms_l");
	Engine::Input::addMap("action1", a);
	a.clear();

	a.push_back("kb_left"); a.push_back("gp_1_x");
	Engine::Input::addMap("left", a);
	a.clear();
	a.push_back("kb_right"); a.push_back("gp_1_b");
	Engine::Input::addMap("right", a);
	a.clear();
	a.push_back("kb_up"); a.push_back("gp_1_y");
	Engine::Input::addMap("up", a);
	a.clear();
	a.push_back("kb_down"); a.push_back("gp_1_a");
	Engine::Input::addMap("down", a);
	a.clear();

	a.push_back("kb_k_w"); a.push_back("gp_1_dpad_u");
	Engine::Input::addMap("W", a);
	a.clear();
	a.push_back("kb_k_a"); a.push_back("gp_1_dpad_l");
	Engine::Input::addMap("A", a);
	a.clear();
	a.push_back("kb_k_s"); a.push_back("gp_1_dpad_d");
	Engine::Input::addMap("S", a);
	a.clear();
	a.push_back("kb_k_d"); a.push_back("gp_1_dpad_r");
	Engine::Input::addMap("D", a);
	a.clear();
}



Game::Game(){
	printf("Project for Physics Based Animation\n(SET09119) Edinburgh Napier University\nSam Serrels\n");
}

void Game::Init(){
	Engine::Engine::Init();
	Engine::Engine::createwindow();

	ent1 = new Engine::EPrimative();
	ent1->SetName("Cool cube");
	Engine::ActiveScene->AddEntity(ent1);

	ent2 = new Engine::EPrimative();
	ent2->SetName("Cool cube2");
	ent2->setPosition(Vector3(3, 0, 0));
	Engine::ActiveScene->AddEntity(ent2);

	camera = new Engine::ECamera();
	camera->Activate();

	registerInputs();
}

void Game::Update(double delta)
{
	//printf("TICK: %f\n", delta*100);
	a+=delta;
//	ent1->setPosition(Vector3(sin(2*a)*1.0f, cos(2*a)*1.0f, 0));

	//camera->setPosition(camera->getPosition() + (Vector3(0, 0, -10.0f)*(float)delta));

	if (Engine::Input::getMapData("action1") > 128){
		printf("action pressed\n");
	}
	Vector3 rot = Vector3(0);
	if (Engine::Input::getMapData("down") > 128){
		rot += Vector3(0,1.0f,0);
	}
	if (Engine::Input::getMapData("up") > 128){
		rot += Vector3(0,-1.0f,0);
	}
	if (Engine::Input::getMapData("left") > 128){
		rot += Vector3(1.0f,0,0);
	}
	if (Engine::Input::getMapData("right") > 128){
		rot += Vector3(-1.0f, 0, 0);
	}
	camera->setRotation(camera->getRotation() + rot*20.0f*(float)delta);

	rot = Vector3(0);
	if (Engine::Input::getMapData("A") > 128){
		rot += Vector3(-1.0f,0, 0);
	}
	if (Engine::Input::getMapData("D") > 128){
		rot += Vector3(1.0f, 0, 0);
	}
	if (Engine::Input::getMapData("S") > 128){
		rot += Vector3(0, 0, 1.0f);
	}
	if (Engine::Input::getMapData("W") > 128){
		rot += Vector3(0, 0,-1.0f);
	}
	camera->setPosition(camera->getPosition() + rot*20.0f*(float)delta);
}

void Game::Shutdown()
{
	delete camera;
	delete ent1;
	Engine::Engine::Shutdown();
}