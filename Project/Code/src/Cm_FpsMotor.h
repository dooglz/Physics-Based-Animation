#pragma once
#include "Engine/Component.h"

class CmFpsMotor: public Engine::CComponent{

protected:
	void registerInputs();
public:
	void Update(double delta);
	CmFpsMotor();
};