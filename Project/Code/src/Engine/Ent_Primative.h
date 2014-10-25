#pragma once
#include "Entity.h"

namespace Engine{
	class Mesh;
	class EPrimative : public Entity{

	protected:
		static Mesh* _CubeMesh;

	public:
		EPrimative();
		~EPrimative();
	};
}