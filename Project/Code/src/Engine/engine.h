#pragma once
#include <string>
namespace Engine {

class Engine {
 protected:
  static bool _running;

 public:
  Engine();
  static void Init();
  static void createwindow();

  static void Update(const double delta);
  static void Render();
  static void SaveFile(const std::string& name);
  static void Stop();

  static bool Run();
  static void Shutdown();

 private:
};
}
