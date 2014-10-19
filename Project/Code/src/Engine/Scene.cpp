#include "Entity.h"
#include "Scene.h"
#include "Renderer.h"

namespace Engine{
	int Scene::Population(){ return _ents.size(); }
	void Scene::AddEntity(Entity* e){}
	bool Scene::RemoveEntity(Entity* e){ return false; }
	const std::vector<Entity*> Scene::GetList(){ return _ents; }

	void Scene::Update(double delta){
		for (std::vector<Entity*>::iterator it = _ents.begin(); it != _ents.end(); ++it) {
			(*it)->Update(delta);
		}
	}

	void Scene::Render(){
		for (std::vector<Entity*>::iterator it = _ents.begin(); it != _ents.end(); ++it) {
			 Renderer->renderMesh((*it)->getMesh(), (*it)->getTranform());
		}
	}

	void Scene::Shutdown(){

	}

}