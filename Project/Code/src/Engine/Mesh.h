#pragma once
#include "Maths.h"
#include "Utilities.h"
#include <vector>

namespace Engine{
	namespace OGL{
		class OGL_ShaderProgram;
	}
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
		#endif
		// mesh data in main memory
		std::vector<stVertex> vertexData;
	};
}