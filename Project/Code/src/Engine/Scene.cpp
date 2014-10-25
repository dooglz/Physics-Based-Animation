#include "Entity.h"
#include "Scene.h"
#include "Renderer.h"

namespace Engine{
	Scene* ActiveScene = NULL;

	int Scene::Population(){ return _ents.size(); }

	void Scene::AddEntity(Entity* e){
		_ents.push_back(e);
	}

	bool Scene::RemoveEntity(Entity* e){ return false; }
	const std::vector<Entity*> Scene::GetList(){ return _ents; }

	void Scene::Update(double delta){
		if (_ents.size() < 1){ return; }
		for (std::vector<Entity*>::iterator it = _ents.begin(); it != _ents.end(); ++it) {
			(*it)->Update(delta);
		}
	}

	void Scene::Render(){
		if (_ents.size() < 1){ return; }
		for (std::vector<Entity*>::iterator it = _ents.begin(); it != _ents.end(); ++it) {
			if ((*it)->getMesh() == nullptr){ continue; }
			Renderer->renderMesh((*it)->getMesh(), (*it)->getTranform());
		}
	}

	void Scene::Shutdown(){

	}

}