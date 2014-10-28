#pragma once
#include "Entity.h"

namespace Engine{
	class Mesh;
	class ECamera : public Entity{

	protected:
		bool _active;
	public:
		//void Update(double delta);
		void Activate();
		void Deactivate();
		bool IsActive();
		ECamera();
		~ECamera();
	};
}