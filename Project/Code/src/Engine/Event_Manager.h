#pragma once
namespace Engine {
class CEventManager {
 protected:
 public:
  virtual void processEvents(){};
  virtual void init(){};
  virtual ~CEventManager(){};
};

extern CEventManager* EventManager;
}