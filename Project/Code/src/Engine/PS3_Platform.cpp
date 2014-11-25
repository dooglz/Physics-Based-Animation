#include "PS3_platform.h"
#include "Utilities.h"
#include "GCM_Renderer.h"

namespace Engine{
	namespace PS3{
		PS3_Platform::PS3_Platform()
		{
			printf("PS3 Platform Loading\n");
		}

		void PS3_Platform::Init()
		{
			Renderer = new GCM::CGCM_Renderer();
		}

		void PS3_Platform::createwindow()
		{

		}

		void PS3_Platform::Shutdown()
		{

		}

	}
}