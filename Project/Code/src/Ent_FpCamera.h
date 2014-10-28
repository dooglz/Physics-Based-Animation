#pragma once
#include "Engine/Ent_camera.h"

class EFpCamera : public Engine::ECamera{

protected:
	void registerInputs();
public:
	void Update(double delta);
	EFpCamera();
};