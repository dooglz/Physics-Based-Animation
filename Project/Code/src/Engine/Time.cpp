#include "Time.h"
#include "Utilities.h"

#if defined(_WINDOWS_)
	#include "sdl/SDL.h"
#endif

namespace Engine{
	//Returns time in Microseconds.
	unsigned long Time::getTime()
	{
		#if defined(_PS3_)
			//microseconds
			return ((unsigned long)(sys_time_get_system_time()));
		#elif defined(_WINDOWS_)
			//milliseconds * 10000
		//	return ((unsigned long)(1000 * SDL_GetTicks()));
			return  (1000000*SDL_GetPerformanceCounter() / SDL_GetPerformanceFrequency());


		#endif
			return 0;
	}
}
