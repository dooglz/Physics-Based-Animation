#pragma once
#include "Event_Manager.h"
namespace Engine{
	namespace PS3{
		class CPS3EventManager : public CEventManager{

		protected:

		public:
			void processEvents();
			void init();
		};
	}
}