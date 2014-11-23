#include "Cm_MeshRenderer.h"
#include "Renderer.h"
#include "Entity.h"
#include "MeshLoader.h"
#include "Mesh.h"

//TODO: remove this
#include "OGL_Renderer.h"
int coolio1;
int coolio2;
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
		//frustrum check
		if (culled){
			unsigned int a = Renderer->GetFrustum().pointAInFrustum(Ent->getPosition());
			if (a == FrustumG::OUTSIDE)
			{
			//	printf("view: %s \t OUTSIDE\n", Ent->GetName());
				
				coolio1++;
				return;
			}
			else if(a == FrustumG::INTERSECT)
			{
			//	printf("view: %s \t INTERSECT%i\n", Ent->GetName());
			}
			else if (a == FrustumG::INSIDE)
			{
			//	printf("view: %s \t INSIDE%i\n", Ent->GetName());
			}

			coolio2++;
		}


		Renderer->renderMesh(_mesh, Ent->getTranform());
	}

}