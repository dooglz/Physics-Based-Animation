#include "Ent_Primative.h"
#include "MeshLoader.h"

namespace Engine{
	Mesh* EPrimative::_CubeMesh;

	EPrimative::EPrimative(){
		_scale = Vector3(1.0f);
		_position = Vector3(0.0f);
		_rotation = Vector3(0.0f);
		CalculateTransform();

		if (_CubeMesh == nullptr)
		{
			_CubeMesh = MeshLoader->openOBJFile("models/cube.obj");
		}
	}

	EPrimative::~EPrimative(){}
}