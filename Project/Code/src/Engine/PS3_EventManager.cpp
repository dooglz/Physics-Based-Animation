#include "PS3_EventManager.h"
#include <sysutil/sysutil_common.h>
#include <sysutil/sysutil_sysparam.h>
#include "Utilities.h"

namespace Engine{
	namespace PS3{

		struct ps3SytemEvent{
			unsigned long long status;
			unsigned long long param;
		};

		static void sysutil_callback(unsigned long long status, unsigned long long  param, void *userdata)
		{
			ps3SytemEvent e;
			e.param = param;
			e.status = status;
			//eventQueue.push_back(e);

		}

		void  CPS3EventManager::processEvents(){}
		void  CPS3EventManager::init(){
			int err = cellSysutilRegisterCallback(0, sysutil_callback, NULL);
			ASSERT("cellSysutilRegisterCallback failed !\n");

		}
	}
}
