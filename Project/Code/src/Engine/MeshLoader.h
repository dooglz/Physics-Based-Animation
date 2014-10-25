#pragma once
#include <String>

namespace Engine{
	//This class is responsible for loading in mesh files, and decoding them to Mesh objects
	class Mesh;
	class CMeshloader{
	protected:

	private:

	public:
		//CMeshloader(){};
		virtual Mesh* openOBJFile(const std::string &filename) = 0;
		virtual void loadOnGPU(Mesh* msh) = 0;
	//	virtual ~CMeshloader() = 0;
	};

	//global public reference to the loader
	extern CMeshloader* MeshLoader;
}