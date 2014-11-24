#include "MeshLoader.h"

namespace Engine{
	Mesh* CMeshloader::getMesh(std::string name)
	{
		//lookup
		std::hash_map<std::string, Mesh*>::iterator got = _meshLibrary.find(name);
		if (got == _meshLibrary.end())
		{
			//Not loaded
			Mesh* _mesh = MeshLoader->openOBJFile(name);
			MeshLoader->loadOnGPU(_mesh);
			_meshLibrary.insert(std::make_pair(name, _mesh));
			return _mesh;
		}
		else
		{
			return got->second;
		}
	}
}