#pragma once
#include "Maths.h"
#include "Utilities.h"
#include <vector>

namespace Engine{
	#if defined(_WINDOWS_)
		namespace OGL{
			class OGL_ShaderProgram;
		}
	#elif defined(_PS3_)
		namespace GCM{
			class GCM_FragmentShader;
			class GCM_VertexShader;
		}
	#endif

	class Mesh{

	protected:

	public:
		bool loadedMain;
		bool loadedLocal;
		int numVerts;
		bool strip;
		bool fan;
		bool line;
		#if defined(_WINDOWS_)

			//! A reference to the shader program to use
			OGL::OGL_ShaderProgram* program;
			
			unsigned int gVBO;
			unsigned int gVAO;
			unsigned int gIBO;

		#elif defined(_PS3_)

			//! A reference to the Fragment shader to use
			GCM::GCM_FragmentShader * fragShader;

			//! A reference to the Vertex shader to use
			GCM::GCM_VertexShader * vertShader;

			//Pointer to the vertex buffer in local memory
			stVertex* vertexBuffer;
			unsigned int vertexBufferOffset;

		#endif

		// mesh data in main memory
		std::vector<stVertex> vertexData;
	};
}