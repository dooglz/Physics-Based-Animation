#pragma once
#include "Entity.h"
#include <vector>

namespace Engine{
//	class Entity;
	class CmCamera;
	class Scene{

	protected:
		std::vector<Entity*> _ents;
		CmCamera* _activeCamera;
	public:
		int Population();
		void AddEntity(Entity* e);
		bool RemoveEntity(Entity* e);
		const std::vector<Entity*> GetList();
		void Update(double delta);
		void Render();
		void Shutdown(); 
		CmCamera* GetActiveCamera();
		void SetActiveCamera(CmCamera* c);
	};


	//global public reference to the renderer
	extern Scene* ActiveScene;
}