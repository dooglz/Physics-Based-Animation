#include "Game.h"
#include "Engine/engine.h"
#include "Engine/Scene.h"
#include "Engine/Input.h"
#include "Engine/Cm_MeshRenderer.h"
#include "Engine/Cm_Camera.h"
#include "Engine/Cm_Physics.h"
#include "Engine/Renderer.h"
#include "Engine/Physics_interface.h"
#include "Cm_FpsMotor.h"

#include <stdio.h>

Engine::Entity* ent1;
Engine::Entity* ent2;
Engine::Entity* ent3;
Engine::Entity* ent4;
Engine::Entity* ent5;
float a = 0.0f;

void Game::registerInputs()
{
	//Todo: read these from file
	//using pushback rather than a={...} as the ps3 compiler is old and dumb
	std::vector<std::string> a;

	a.push_back("kb_space"); a.push_back("gp_1_start"); a.push_back("ms_l");
	Engine::Input::addMap("action1", a);
	a.clear();
	a.push_back("ms_r");
	Engine::Input::addMap("action2", a);
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
	ent1->setPosition(Vector3(3, 4, -3));
	ent1->AddComponent(new Engine::CmMeshRenderer());
	ent1->getComponent<Engine::CmMeshRenderer>()->setMesh("models/cube.obj");
	ent1->AddComponent(new Engine::CmPhysics_Cuboid(10,ent1->getPosition(),ent1->getRotation(), ent1->getScale().x, ent1->getScale().y, ent1->getScale().z));
	ent1->getComponent<Engine::CmPhysics_Cuboid>()->SetUsesGravity(true);
	Engine::ActiveScene->AddEntity(ent1);

	ent4 = new Engine::Entity();
	ent4->SetName("Cool sphere");
	ent4->setPosition(Vector3(3, 5, 3));
	ent4->AddComponent(new Engine::CmMeshRenderer());
	ent4->getComponent<Engine::CmMeshRenderer>()->setMesh("models/sphere.obj");
	ent4->AddComponent(new Engine::CmPhysics_Sphere(10, ent4->getPosition(), ent1->getRotation(), ent4->getScale().x));
	ent4->getComponent<Engine::CmPhysics_Sphere>()->SetUsesGravity(true);
	Engine::ActiveScene->AddEntity(ent4);
	/*
	ent5 = new Engine::Entity();
	ent5->SetName("Cool sphere 2");
	ent5->setPosition(Vector3(6, 5, -2));
	ent5->setScale(Vector3(2, 2, 2));
	ent5->AddComponent(new Engine::CmMeshRenderer());
	ent5->getComponent<Engine::CmMeshRenderer>()->setMesh("models/sphere.obj");
	ent5->AddComponent(new Engine::CmPhysics_Sphere(40, ent5->getPosition(), ent5->getScale().x));
	ent5->getComponent<Engine::CmPhysics_Sphere>()->SetUsesGravity(true);
	Engine::ActiveScene->AddEntity(ent5);
	*/
	ent2 = new Engine::Entity();
	ent2->SetName("floor");
	ent2->setPosition(Vector3(0, 0, 0));
	ent2->setScale(Vector3(30, 1,30));
	ent2->AddComponent(new Engine::CmMeshRenderer());
	ent2->getComponent<Engine::CmMeshRenderer>()->setMesh("models/plane.obj");
	ent2->AddComponent(new Engine::CmPhysics_Plane(Vector3(0, 0, 0), Vector3(0, 1, 0)));
	Engine::ActiveScene->AddEntity(ent2);
	/*
	for (int i = 0; i < 10; i++)
	{
		Engine::Entity* e = new Engine::Entity();
		e->SetName("Cool spher");
		e->setPosition(Vector3(0, i*2.5f, 0));
		e->AddComponent(new Engine::CmMeshRenderer());
		e->getComponent<Engine::CmMeshRenderer>()->setMesh("models/sphere.obj");
		e->AddComponent(new Engine::CmPhysics_Sphere(10, e->getPosition(), 1.0f));
		e->getComponent<Engine::CmPhysics_Sphere>()->SetUsesGravity(true);
		Engine::ActiveScene->AddEntity(e);
	}
	*/
	ent3 = new Engine::Entity();
	ent3->SetName("Camera");
	ent3->setPosition(Vector3(-3.0, 2.5, 3.0));
	ent3->setRotation(Vector3(0.00f,-1.2f, 0));
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
		//printf("action pressed\n");
		//Engine::ActiveScene->report();
		Engine::PhysicsTickEnabled = false;
	}
	if (Engine::Input::getMapData("action2") > 128){
		Engine::PhysicsTickEnabled = true;
	}

//	Engine::Renderer->DrawLine(Vector3(0.0f), Vector3(3 * sin(a), 3.5f, 3 * cos(a)));

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