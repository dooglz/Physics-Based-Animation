#pragma once
#include "Maths.h"
#include <vector>

namespace Engine{
	class Mesh{

	protected:

	public:
		bool loadedMain;
		bool loadedLocal;
		int numVerts;
		bool strip;
		bool fan;
		bool line;

		// mesh data in main memory
		std::vector<stVertex> vertexData;
	};
}