#include "Ent_Primative.h"
#include "MeshLoader.h"
#include "Mesh.h"
#include "OGL_Renderer.h"

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
			MeshLoader->loadOnGPU(_CubeMesh);
			_CubeMesh->program = OGL::COGL_Renderer::GetDefaultShaderProgram();
		}
		_mesh = _CubeMesh;
	}

	EPrimative::~EPrimative(){}
}