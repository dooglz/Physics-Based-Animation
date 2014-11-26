#include "Entity.h"
#include "Scene.h"
#include "Renderer.h"
#include "Cm_Camera.h"

extern Matrix4 oviewMatrix;

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
		#if defined(_PC_)
			viewMat = _activeCamera->GetParent()->getTranform();
			viewMat = Inverse(viewMat);
		#elif defined(_PS3_)
			//viewMat = lookat(_activeCamera->GetParent()->getPosition(), Vector3(0, 0, 0), Vector3(0, 1.0f, 0));
			viewMat = oviewMatrix;
		#endif
			Renderer->SetViewMatrix(viewMat);
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