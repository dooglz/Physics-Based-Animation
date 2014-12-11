#pragma once
#include "platform.h"

namespace Engine {
namespace GCM {
class CGCM_Renderer;
}
namespace PS3 {
class PS3_Platform : public CPlatform {
 private:
 protected:
  static bool _running;
  GCM::CGCM_Renderer* _renderer;

 public:
  PS3_Platform();
  void Init();
  void createwindow();
  void Shutdown();

  void SaveFile(const std::string& name){};
};
}
}
