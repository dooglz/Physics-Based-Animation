#include "Time.h"
#include "Utilities.h"

#if defined(_WINDOWS_)
	#include "sdl/SDL.h"
#endif

namespace Engine{
	//Returns time in Microseconds.
	double Time::getTime()
	{
		#if defined(_PS3_)
			//microseconds
			return ((unsigned long)(sys_time_get_system_time()));
		#elif defined(_WINDOWS_)
			//milliseconds * 10000
		//	return ((unsigned long)(1000 * SDL_GetTicks()));
			return  (double)(SDL_GetPerformanceCounter() / SDL_GetPerformanceFrequency());


		#endif
			return 0;
	}
}
