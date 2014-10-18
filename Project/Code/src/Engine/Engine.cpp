#include "engine.h"
#include "physics.h"
#include "SDL_platform.h"

namespace Engine{
	bool Engine::_running;
	Platform* Engine::_platform;

	Engine::Engine()
	{

	}

	void Engine::Init()
	{
		_platform = new SDL::SDL_Platform();
		Physics::Init();
		_running = true;
	}

	void Engine::createwindow()
	{
		_platform->createwindow();
	}

	void Engine::Update(double delta)
	{

	}

	void Engine::Render()
	{

	}

	bool Engine::Run()
	{
		return _running;
	}

	void Engine::Shutdown()
	{

	}
}
