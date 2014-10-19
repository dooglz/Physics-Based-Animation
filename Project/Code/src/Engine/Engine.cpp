#include "engine.h"
#include "physics.h"
#include "Renderer.h"
#include "SDL_platform.h"
#include "Scene.h"

namespace Engine{
	bool Engine::_running;
	Platform* Engine::_platform;
	Scene* Engine::_scene;

	Engine::Engine()
	{

	}

	void Engine::Init()
	{
		_platform = new SDL::SDL_Platform();
		_platform->Init();
		Physics::Init();
		_scene = new Scene();
		_running = true;
		printf("%p\n", Renderer);
	}

	void Engine::createwindow()
	{
		_platform->createwindow();
	}

	void Engine::Update(double delta)
	{
		_scene->Update(delta);
	}

	void Engine::Render()
	{
		Renderer->PrepFrame();
		_scene->Render();
		Renderer->PostRender();
	}

	bool Engine::Run()
	{
		return _running;
	}

	void Engine::Shutdown()
	{
		_scene->Shutdown();
		delete _scene;
		_platform->Shutdown();
		delete _platform;
	}
}
