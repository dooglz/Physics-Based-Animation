#include "engine.h"
#include "physics.h"

namespace Engine{
	bool Engine::_running;

	Engine::Engine()
	{

	}

	void Engine::Init()
	{
		Physics::Init();
		_running = true;
	}

	void Engine::createwindow()
	{

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
