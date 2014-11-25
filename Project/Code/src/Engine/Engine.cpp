
#include "engine.h"
#include "physics_Interface.h"
#include "Renderer.h"
#include "platform.h"
#include "Event_Manager.h"
#include "MeshLoader.h"
#include "Scene.h"

#if defined _PC_
	#include "SDL_platform.h"
	#include "SDL_EventManager.h"
	#include "SDL_MeshLoader.h"
#elif defined _PS3_
	#include "PS3_platform.h"
	#include "PS3_EventManager.h"
	#include "GCM_MeshLoader.h"
#endif

#if defined BULLET
//#include "BulletSolver.h"
#else
#include "CustomPhysicsSolver.h"
#endif

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
		#if defined _PC_
			Platform = new SDL::SDL_Platform();
		#elif defined _PS3_
			Platform = new PS3::PS3_Platform();
		#endif

		Platform->Init();

		#if defined _PC_
			EventManager = new SDL::CSDL_EventManager();
		#elif defined _PS3_
			EventManager = new PS3::CPS3EventManager();
		#endif
		
		EventManager->init();

		#if defined BULLET
			//PhysicsSolver = new CBulletSolver();
		#else
			PhysicsSolver = new CCustomSover();
		#endif

		PhysicsSolver->Init();

		#if defined _PC_
			MeshLoader = new SDL::CSDL_Meshloader();
		#elif defined _PS3_
			MeshLoader = new GCM::CGCM_Meshloader();
		#endif

		ActiveScene = new Scene();

		_running = true;
	}

	void Engine::createwindow()
	{
		Platform->createwindow();
	}

	void Engine::Update(const double delta)
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

	void Engine::SaveFile(const std::string& name)
	{
		Platform->SaveFile(name);
	}

}
