#pragma once
#include "Component.h"

namespace Engine{
	class Mesh;
	class CmMeshRenderer : public CComponent{

	protected:
		Mesh* _mesh;
	public:
		CmMeshRenderer(Entity* Parent);
		~CmMeshRenderer();
		Mesh* getMesh();
		void setMesh(Mesh* msh);
		void setMesh(std::string meshname);
		void Render();
	};
}