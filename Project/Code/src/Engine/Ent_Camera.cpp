#pragma once
#include "Ent_Camera.h"
#include "Scene.h"

namespace Engine{

	ECamera::ECamera(){
		_scale = Vector3(1.0f);
		_position = Vector3(0.0f);
		_rotation = Vector3(0.0f);
		CalculateTransform();
	}

	ECamera::~ECamera()
	{

	}

	void ECamera::Activate(){
		_active = true;
		ActiveScene->SetActiveCamera(this);
	}

	void ECamera::Deactivate(){
		_active = false;
		ActiveScene->SetActiveCamera(NULL);
	}

	bool ECamera::IsActive(){
		return _active;
	}
}