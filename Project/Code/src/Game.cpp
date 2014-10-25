#include "Game.h"
#include "Engine/engine.h"
#include "Engine/Ent_Primative.h"
#include "Engine/Scene.h"
#include <stdio.h>

Engine::Entity* ent1;
float a = 0.0f;

Game::Game(){
	printf("Project for Physics Based Animation\n(SET09119) Edinburgh Napier University\nSam Serrels\n");
}

void Game::Init(){
	Engine::Engine::Init();
	Engine::Engine::createwindow();

	ent1 = new Engine::EPrimative();
	ent1->SetName("Cool cube");
	Engine::ActiveScene->AddEntity(ent1);
}

void Game::Update(double delta)
{
	//printf("TICK: %f\n", delta*100);
	a+=delta;
	ent1->setPosition(Vector3(sin(a)*100.0f, 0, 0));
}

void Game::Shutdown()
{
	Engine::Engine::Shutdown();
}