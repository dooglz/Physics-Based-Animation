#include "Game.h"
#include "Engine/engine.h"

#include <stdio.h>


Game::Game(){
	printf("Project for Physics Based Animation\n(SET09119) Edinburgh Napier University\nSam Serrels\n");
}

void Game::Init(){
	Engine::Engine::Init();
	Engine::Engine::createwindow();

}

void Game::Update(double delta)
{

}

void Game::Shutdown()
{
	Engine::Engine::Shutdown();
}