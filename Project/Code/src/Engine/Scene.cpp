#include "Entity.h"
#include "Scene.h"
#include "Renderer.h"
#include "Cm_Camera.h"

namespace Engine{
	Scene* ActiveScene = NULL;

	int Scene::Population()const{ return _ents.size(); }

	void Scene::AddEntity(Entity*const e){
		//TODO: check to see if already have entitiy
		_ents.push_back(e);
	}

	bool Scene::RemoveEntity(Entity*const e){ return false; }
	const std::vector<Entity*> Scene::GetList(){ return _ents; }

	void Scene::Update(const double delta){
		if (_ents.size() < 1){ return; }
		for (std::vector<Entity*>::iterator it = _ents.begin(); it != _ents.end(); ++it) {
			(*it)->Update(delta);
		}
	}

	void Scene::Render(){
		if (_ents.size() < 1){ return; }
		Matrix4 viewMat;
		if (_activeCamera == NULL){
			printf("No active Camera in Scene!\n");
			Renderer->SetViewMatrix(Matrix4(1.0f));
		}else{
			Renderer->SetViewMatrix(Inverse(_activeCamera->GetParent()->getTranform()));
		}

		for (std::vector<Entity*>::iterator it = _ents.begin(); it != _ents.end(); ++it) {
			(*it)->Render();
		}
	}

	void Scene::Shutdown(){

	}

	CmCamera* Scene::GetActiveCamera() const
	{
		return _activeCamera;
	}

	void Scene::SetActiveCamera(CmCamera*const c)
	{
		if (_activeCamera != NULL){
			_activeCamera->Deactivate();
		}
		_activeCamera = c;
	}

	void Scene::report() const
	{
		printf("Scene report -- Ents:%i\n", _ents.size());
		for (std::vector<Entity*>::const_iterator it = _ents.begin(); it != _ents.end(); ++it) {
			printf("%s - (%i,%i,%i)\n", (*it)->GetName(), (*it)->getPosition().getX(), (*it)->getPosition().getY(), (*it)->getPosition().getZ());
		}
	}
}