#pragma once
#include <String>
#include <unordered_map>

namespace Engine{
	//This class is responsible for loading in mesh files, and decoding them to Mesh objects
	class Mesh;
	class CMeshloader{
	protected:
		std::unordered_map<std::string, Mesh*> _meshLibrary;
	private:

	public:
		//CMeshloader(){};
		virtual Mesh* openOBJFile(const std::string &filename) = 0;
		virtual void loadOnGPU(Mesh* msh) = 0;
	//	virtual ~CMeshloader() = 0;
		Mesh* getMesh(std::string name);
	};

	//global public reference to the loader
	extern CMeshloader* MeshLoader;
}