#pragma once
#include "platform.h"
#include <sdl/SDL.h>


namespace Engine{
	namespace SDL{
		class SDL_Platform : public CPlatform
		{
		private:

		protected:
			static bool _running;
			static SDL_Window* _window;
			static SDL_GLContext _gContext;
			unsigned char _glverMaj;
			unsigned char _glverMin;
			
		public:
			SDL_Platform();
			void Init();
			void createwindow();
			void Shutdown();

			static void CheckGL();
			static void CheckSDL();

			static SDL_Window* GetWindow(){ return _window; };
			void SaveFile(const std::string& name);
		};
	}
}
