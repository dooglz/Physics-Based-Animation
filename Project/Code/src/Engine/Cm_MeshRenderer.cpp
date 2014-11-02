#include "MeshRenderer.h"
#include "Renderer.h"
#include "Entity.h"
#include "MeshLoader.h"
#include "Mesh.h"

//TODO: remove this
#include "OGL_Renderer.h"

namespace Engine{

	CmMeshRenderer::CmMeshRenderer() : CComponent("MeshRenderer"){
		
	}

	CmMeshRenderer::~CmMeshRenderer()
	{

	}

	Mesh* CmMeshRenderer::getMesh()
	{ 
		return _mesh;
	}

	void CmMeshRenderer::setMesh(Mesh* msh)
	{ 
		_mesh = msh;
	}

	void CmMeshRenderer::setMesh(std::string meshname)
	{
		//TODO: Have an actual meshloader platform
		_mesh = MeshLoader->getMesh(meshname);
		MeshLoader->loadOnGPU(_mesh);
		_mesh->program = OGL::COGL_Renderer::GetDefaultShaderProgram();

	}

	void CmMeshRenderer::Render()
	{
		ASSERT(_mesh != nullptr);
		Renderer->renderMesh(_mesh, Ent->getTranform());
	}

}