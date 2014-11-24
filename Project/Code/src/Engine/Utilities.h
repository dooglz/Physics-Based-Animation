#pragma once

#if defined(__psp2__)
	#define _vita_
#elif defined(__PPU__) || defined(__SPU__)
	#define _PS3_
#elif defined( XBOX360 )
	#define XBOX360
#elif defined(_MSC_VER) ||  defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__) || defined(MINGW32)
	#define _WINDOWS_
	#define _PC_
	//disable stupid _s crt reqs
	#define _CRT_SECURE_NO_DEPRECATE
	#pragma warning (disable : 4996)
#elif defined( APPLE ) //This works, but it could be either an OSX or iOS device
	#define _MAC_
	#define _PC_
#elif defined( linux ) || (defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__)))
	#define _LINUX_
	#define _PC_
#else
	#error unknown platform
#endif

#if defined(_PC_)
#include "sdl/SDL_assert.h"
#endif

// −− Platform specific halts

#if defined(_vita_)
	#include "libdbg.h"
	#define HALT _SCE_BREAK();
#elif defined(_PS3_)
	#include <stdio.h>
	#include <stdlib.h>	
	//#define HALT { __asm__ volatile( "trap" ); }
	#define HALT { exit (1); }
#elif defined(_XBOX360_)
	//#define HALT  __debugbreak
	#define HALT __asm {int 3}
#elif defined(_PC_)
	#define HALT SDL_TriggerBreakpoint();
#else
	#error HALT: unknown platform
#endif


#if defined(_PC_)
	//Use the cool SDL assert
	#define ASSERT(exp) SDL_assert(exp)
	#define ASSERT_MSG( exp, smsg ) SDL_assert(exp)
	#define ASSERT_FUNC( exp, func) SDL_assert(exp)
#else
	// call HALT on assert fail
	#define ASSERT(exp) { if ( !(exp) ) {HALT;} }
	// Prints the suplied string on assert fail, then call HALT
	#define ASSERT_MSG( exp, smsg ) { if ( !(exp) ) {puts (smsg); HALT;} }
	// Calls the suplied function on assert fail, then call HALT
	#define ASSERT_FUNC( exp, func) { if ( !(exp) ) {func; HALT;} }
#endif

// −− Platform specific Utility Libs
#if defined(_vita_)
	#define FILE_PATH "app0:"
#elif defined(_PS3_)
	#define FILE_PATH SYS_APP_HOME + std::string("/")
#elif defined(_XBOX360_) || defined(_WINDOWS_)
	//#define uint32_t unsigned int
	//#define uint16_t unsigned int
	#define FILE_PATH ""
#endif
