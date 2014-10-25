#include "engine.h"
#include "physics.h"
#include "Renderer.h"
#include "MeshLoader.h"
#include "Scene.h"

#include "SDL_platform.h"
#include "SDL_MeshLoader.h"


namespace Engine{
	bool Engine::_running;
	Platform* Engine::_platform;
	CMeshloader* MeshLoader = NULL;

	Engine::Engine()
	{

	}

	void Engine::Init()
	{
		_platform = new SDL::SDL_Platform();
		_platform->Init();

		Physics::Init();

		MeshLoader = new SDL::CSDL_Meshloader();

		ActiveScene = new Scene();

		_running = true;
	}

	void Engine::createwindow()
	{
		_platform->createwindow();
	}

	void Engine::Update(double delta)
	{
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

	void Engine::Shutdown()
	{
		ActiveScene->Shutdown();
		delete ActiveScene;
		delete MeshLoader;
		_platform->Shutdown();
		delete _platform;
	}

}
