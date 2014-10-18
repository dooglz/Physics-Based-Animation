#pragma once
#include "platform.h"
#include <sdl/SDL.h>


namespace Engine{
	namespace SDL{
		class SDL_Platform : public Platform
		{
		private:

		protected:
			static bool _running;
			SDL_Window* _window;
			SDL_GLContext _gContext;
			unsigned char _glverMaj;
			unsigned char _glverMin;
			unsigned int _displayHeight;
			unsigned int _displayWidth;
		public:
			SDL_Platform();
			void Init();
			void createwindow();
			void Shutdown();


		};
	}
}
