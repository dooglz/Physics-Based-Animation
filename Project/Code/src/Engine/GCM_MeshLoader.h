#pragma once
#include "MeshLoader.h"
#include "Utilities.h"  // asserts and commmon defines
#include "Maths.h"

namespace Engine {
namespace GCM {
// This clas sis responsible for loading in mesh files, and decoding them to
// Mesh objects
class CGCM_Meshloader : public CMeshloader {
 protected:
  bool loadOBJ(const char* path, std::vector<stvec3>& out_vertices,
               std::vector<stvec2>& out_uvs, std::vector<stvec3>& out_normals);

 private:
 public:
  CGCM_Meshloader(){};
  Mesh* openOBJFile(const std::string& filename);
  void loadOnGPU(Mesh* msh);
  ~CGCM_Meshloader(){};
};
}
}