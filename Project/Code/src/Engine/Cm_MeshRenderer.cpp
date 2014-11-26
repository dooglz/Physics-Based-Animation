#include "Cm_MeshRenderer.h"
#include "Renderer.h"
#include "Entity.h"
#include "MeshLoader.h"
#include "Mesh.h"

//TODO: remove this
#include "OGL_Renderer.h"
int culledObjects;
int renderedObjects;
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
		#if defined _PC_
			_mesh->program = OGL::COGL_Renderer::GetDefaultShaderProgram();
		#endif
	}

	void CmMeshRenderer::Render()
	{
		ASSERT(_mesh != NULL);
		//frustrum check
		if (culled){
			float distance = Dot(Renderer->aan, (Ent->getPosition() - Renderer->aap));
			if (distance < 0){
				culledObjects++;
			//	return;
			}
		}
		renderedObjects++;
#if defined(_PC_)
		Renderer->renderMesh(_mesh, Ent->getTranform());
#elif defined(_PS3_)
		Matrix4 trn = Matrix4::translation(-Ent->getPosition()) *  Matrix4::scale(Ent->getScale());
		Renderer->renderMesh(_mesh, trn);
#endif
	}

}