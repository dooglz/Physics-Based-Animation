#pragma once
#define COMMAND_SIZE (65536) // 64 KB
#define BUFFER_SIZE (1024*1024) //1MB

#include "Utilities.h"		// asserts and commmon defines
#include "Renderer.h"		// asserts and commmon defines
#include "GCM_FragmentShader.h"
#include "GCM_VertexShader.h"
#include <cell/gcm.h>	//for CGprogram
#include <vector>

namespace Engine{
	namespace GCM{
		class CGCM_Renderer : public CRenderer{

		protected:
			static void loadShaders();
			//static std::vector<Vector3 const> linebuffer;
			void ProcessLines(){};
		private:

			uint32_t screenHeight;
			uint32_t screenWidth;
			bool _swapFlag;

			//! The array of render surfaces.
			static CellGcmSurface _surfaces[_numberOfSurfaces];

			//! A reference to the current Fragment shader in use
			static GCM_FragmentShader * _currentFrag;

			//! A reference to the current Vertex shader in use
			static GCM_VertexShader * _currentVert;

			//! A reference to the default Fragment shader
			static GCM_FragmentShader * defaultFrag;

			//! A reference to the default Vertex shader
			static GCM_VertexShader * defaultVert;

		public:
			CGCM_Renderer(void);
			~CGCM_Renderer();
			void renderMesh(Mesh*const msh, const Matrix4& mvp);
			void DrawLine(const Vector3& p1, const Vector3& p2);
			void DrawCross(const Vector3& p1, const float size);
			void PrepFrame();
			void PostRender();
			void clearSurface();

			//static void sysutil_callback(uint64_t status, uint64_t param, void *userdata);

			void assignShader(Mesh* m, std::string name);

			//! Output screen ratio, width/height
			float screenRatio;

			//! Detect and set resolution
			void InitDisplay();

			//! Create Buffers/surfaces in memory
			void InitSurfaces();

			void loadDefaultShaders();

			//! Switch which buffer is active(being rendered on) and currentyl displayed
			void swapBuffers();

			//! Set the active vertex and fragment shader
			static void SetCurrentShader(GCM_VertexShader & vert, GCM_FragmentShader & frag);

			//! Initialises viewport (coordinate scaling)
			void SetViewport();

			void Shutdown();

			//TODO: put these in a struct or something
			uint32_t color_pitch;
			uint32_t color_size;
			uint32_t depth_pitch;
			uint32_t depthSize;

			
		};
	}
}