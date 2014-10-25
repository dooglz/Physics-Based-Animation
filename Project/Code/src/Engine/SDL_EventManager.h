#pragma once
#include "Event_Manager.h"
namespace Engine{
	namespace SDL{
		class CSDL_EventManager : public CEventManager{

		protected:

		public:
			void processEvents();
			void init();
		};
	}
}