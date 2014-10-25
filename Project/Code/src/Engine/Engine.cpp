#include "engine.h"
#include "physics.h"
#include "Renderer.h"
#include "MeshLoader.h"
#include "Scene.h"

#include "SDL_platform.h"
#include "SDL_EventManager.h"
#include "SDL_MeshLoader.h"


namespace Engine{
	bool Engine::_running;
	CPlatform* Platform = NULL;
	CMeshloader* MeshLoader = NULL;
	CEventManager* EventManager = NULL;

	Engine::Engine()
	{

	}

	void Engine::Init()
	{
		Platform = new SDL::SDL_Platform();
		Platform->Init();

		EventManager = new SDL::CSDL_EventManager();
		EventManager->init();

		Physics::Init();

		MeshLoader = new SDL::CSDL_Meshloader();

		ActiveScene = new Scene();

		_running = true;
	}

	void Engine::createwindow()
	{
		Platform->createwindow();
	}

	void Engine::Update(double delta)
	{
		EventManager->processEvents();
		ActiveScene->Update(delta);
	}

	void Engine::Render()
	{
		Renderer->PrepFrame();
		ActiveScene->Render();
		Renderer->PostRender();
	}

	bool Engine::Run()
	{
		return _running;
	}

	void Engine::Stop()
	{
		_running = false;
	}

	void Engine::Shutdown()
	{
		ActiveScene->Shutdown();
		delete ActiveScene;
		delete MeshLoader;
		Platform->Shutdown();
		delete Platform;
	}

}
