#include "Entity.h"
#include "Scene.h"
#include "Renderer.h"
#include "Cm_Camera.h"

namespace Engine{
	Scene* ActiveScene = NULL;

	int Scene::Population(){ return _ents.size(); }

	void Scene::AddEntity(Entity* e){
		//TODO: check to see if already have entitiy
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
		Matrix4 viewMat;
		if (_activeCamera == NULL){
			printf("No active Camera in Scene!\n");
			Renderer->SetViewMatrix(Matrix4(1.0f));
		}else{
			Renderer->SetViewMatrix(Inverse(_activeCamera->GetParent()->getTranform()));
			//viewMat = _activeCamera->getTranform();
			//viewMat = Lookat(_activeCamera->getPosition(), Vector3(_activeCamera->getTranform()[2]), Vector3(_activeCamera->getTranform()[1]));
		}

		for (std::vector<Entity*>::iterator it = _ents.begin(); it != _ents.end(); ++it) {
			(*it)->Render();
		}

		for (std::vector<Entity*>::iterator it = _ents.begin(); it != _ents.end(); ++it) {
//			if ((*it)->getMesh() == nullptr){ continue; }
	//		Renderer->renderMesh((*it)->getMesh(), viewMat * (*it)->getTranform());
		}
	}

	void Scene::Shutdown(){

	}

	CmCamera* Scene::GetActiveCamera()
	{
		return _activeCamera;
	}
	void Scene::SetActiveCamera(CmCamera* c)
	{
		if (_activeCamera != NULL){
			_activeCamera->Deactivate();
		}
		_activeCamera = c;
	}
}