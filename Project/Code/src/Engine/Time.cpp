#include "Time.h"
#include "Utilities.h"

#if defined(_WINDOWS_)
	#include "sdl/SDL.h"
#elif defined(_PS3_)
	#include <sys/sys_time.h>
#endif
namespace Engine{
	//Returns time in Seconds.
	double Time::getTime()
	{
		#if defined(_PS3_)
			//microseconds
			return ((unsigned long)(sys_time_get_system_time()));
		#elif defined(_WINDOWS_)
			return  ((double)(SDL_GetPerformanceCounter()) / ((double)SDL_GetPerformanceFrequency()));
		#endif
			return 0;
	}
}
