#include "GCM_Renderer.h"
namespace Engine{
	namespace GCM{

		CGCM_Renderer::CGCM_Renderer(){};

		CGCM_Renderer::~CGCM_Renderer(){};

		void CGCM_Renderer::renderMesh(Mesh*const msh, const Matrix4& mvp){}
		void CGCM_Renderer::DrawLine(const Vector3& p1, const Vector3& p2){}
		void CGCM_Renderer::DrawCross(const Vector3& p1, const float size){}
		void CGCM_Renderer::PrepFrame(){}
		void CGCM_Renderer::PostRender(){}
		void CGCM_Renderer::clearSurface(){}

		void CGCM_Renderer::sysutil_callback(uint64_t status, uint64_t param, void *userdata){}

		void CGCM_Renderer::assignShader(Mesh* m, std::string name){}

		//! Detect and set resolution
		void CGCM_Renderer::InitDisplay(){}

		//! Create Buffers/surfaces in memory
		void CGCM_Renderer::InitSurfaces(){}

		void CGCM_Renderer::loadDefaultShaders(){}

		void CGCM_Renderer::setupFrame(){}

		//! Switch which buffer is active(being rendered on) and currentyl displayed
		void CGCM_Renderer::swapBuffers(){}

		//! Set the active vertex and fragment shader
		void CGCM_Renderer::SetCurrentShader(GCM_VertexShader & vert, GCM_FragmentShader & frag){}

		//! Initialises viewport (coordinate scaling)
		void CGCM_Renderer::SetViewport(){}

		void CGCM_Renderer::shutdown(){}

	
	}
}