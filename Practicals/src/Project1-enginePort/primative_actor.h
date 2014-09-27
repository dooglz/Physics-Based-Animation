#pragma once
#include "sharp-blue/Actor.h"
#include <vector>

static enum stPrimitive_type
{
	CUBE, SPHERE
}; 

class CPrimative : public Engine::Actor{
private:

public:
	CPrimative(){};
	CPrimative(stPrimitive_type type);
	void update(float delta);
	void render();
};