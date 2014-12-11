#include "PS3_platform.h"
#include "Utilities.h"
#include "GCM_Renderer.h"

namespace Engine {
namespace PS3 {
PS3_Platform::PS3_Platform() { printf("PS3 Platform Loading\n"); }

void PS3_Platform::Init() {
  _renderer = new GCM::CGCM_Renderer();
  Renderer = _renderer;
}

void PS3_Platform::createwindow() { _renderer->InitDisplay(); }

void PS3_Platform::Shutdown() {
  _renderer->Shutdown();
  delete _renderer;
  Renderer = NULL;
}
}
}