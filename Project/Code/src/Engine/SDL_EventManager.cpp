#include "SDL_EventManager.h"
#include "engine.h"
#include "Utilities.h"
#include "sdl\SDL.h"
#include "Input.h"

namespace Engine{
	namespace SDL{

		void CSDL_EventManager::processEvents(){
			SDL_Event e;
			while (SDL_PollEvent(&e) != 0)
			{
				switch (e.type)
				{
				case SDL_QUIT: {
					Engine::Stop();
					break;
				}

					//INPUT EVENTS --#
				case SDL_KEYDOWN: {
					switch (e.key.keysym.sym) {
						//function keys
					case SDLK_SPACE:{
						Input::setValue("kb_space", 255);
						break;
					}
					case SDLK_ESCAPE:{
						Engine::Stop();
						break;
					}

					case SDLK_RETURN:{
						Input::setValue("kb_enter", 255);
						break;
					}
						//arrowkeys
					case SDLK_UP:{
						Input::setValue("kb_up", 255);
						break;
					}
					case SDLK_LEFT:{
						Input::setValue("kb_left", 255);
						break;
					}
					case SDLK_RIGHT:{
						Input::setValue("kb_right", 255);
						break;
					}
					case SDLK_DOWN:{
						Input::setValue("kb_down", 255);
						break;
					}
						//wasd
					case SDLK_w:{
						Input::setValue("kb_k_w", 255);
						break;
					}
					case SDLK_a:{
						Input::setValue("kb_k_a", 255);
						break;
					}
					case SDLK_s:{
						Input::setValue("kb_k_s", 255);
						break;
					}
					case SDLK_d:{
						Input::setValue("kb_k_d", 255);
						break;
					}

						//ijkl
					case SDLK_i:{
						Input::setValue("kb_k_i", 255);
						break;
					}
					case SDLK_j:{
						Input::setValue("kb_k_j", 255);
						break;
					}
					case SDLK_k:{
						Input::setValue("kb_k_k", 255);
						break;
					}
					case SDLK_l:{
						Input::setValue("kb_k_l", 255);
						break;
					}
					}
					break;
				}
				case SDL_KEYUP: {
					switch (e.key.keysym.sym) {
					case SDLK_SPACE:{
						Input::setValue("kb_space", 0);
						break;
					}
					case SDLK_RETURN:{
						Input::setValue("kb_enter", 0);
						break;
					}
					case SDLK_UP:{
						Input::setValue("kb_up", 0);
						break;
					}
					case SDLK_LEFT:{
						Input::setValue("kb_left", 0);
						break;
					}
					case SDLK_RIGHT:{
						Input::setValue("kb_right", 0);
						break;
					}
					case SDLK_DOWN:{
						Input::setValue("kb_down", 0);
						break;
					}
						//wasd
					case SDLK_w:{
						Input::setValue("kb_k_w", 0);
						break;
					}
					case SDLK_a:{
						Input::setValue("kb_k_a", 0);
						break;
					}
					case SDLK_s:{
						Input::setValue("kb_k_s", 0);
						break;
					}
					case SDLK_d:{
						Input::setValue("kb_k_d", 0);
						break;
					}
						//ijkl
					case SDLK_i:{
						Input::setValue("kb_k_i", 0);
						break;
					}
					case SDLK_j:{
						Input::setValue("kb_k_j", 0);
						break;
					}
					case SDLK_k:{
						Input::setValue("kb_k_k", 0);
						break;
					}
					case SDLK_l:{
						Input::setValue("kb_k_l", 0);
						break;
					}
					}
					break;
				}
				case SDL_MOUSEMOTION: {
					break;
				}
				case SDL_MOUSEBUTTONDOWN: {
					switch (e.button.button) {
					case SDL_BUTTON_LEFT: {
						Input::setValue("ms_l", 255);
						break;
					}
					case SDL_BUTTON_RIGHT: {
						Input::setValue("ms_r", 255);
						break;
					}
					case SDL_BUTTON_MIDDLE: {
						break;
					}
					}
					break;
				}
				case SDL_MOUSEBUTTONUP:    {
					switch (e.button.button) {
					case SDL_BUTTON_LEFT: {
						Input::setValue("ms_l", 0);
						break;
					}
					case SDL_BUTTON_RIGHT: {
						Input::setValue("ms_r", 0);
						break;
					}
					case SDL_BUTTON_MIDDLE: {
						break;
					}
					}
					break;
				}
				case SDL_JOYAXISMOTION: {
					break;
				}
				case SDL_JOYBALLMOTION: {
					break;
				}
				case SDL_JOYHATMOTION: {
					break;
				}
				case SDL_JOYBUTTONDOWN: {
					break;
				}
				case SDL_JOYBUTTONUP: {
					break;
				}
				default: {
					break;
				}
				}
				//End switch
			}
			//End While

		}

		void CSDL_EventManager::init(){
			printf("SDLEventManager Init \n");
			Input::addAxis("ms_l");
			Input::addAxis("ms_r");
			Input::addAxis("kb_up");
			Input::addAxis("kb_down");
			Input::addAxis("kb_left");
			Input::addAxis("kb_right");
			Input::addAxis("kb_space");
			Input::addAxis("kb_enter");
			//wasd
			Input::addAxis("kb_k_w");
			Input::addAxis("kb_k_a");
			Input::addAxis("kb_k_s");
			Input::addAxis("kb_k_d");
			//ijkl
			Input::addAxis("kb_k_i");
			Input::addAxis("kb_k_j");
			Input::addAxis("kb_k_k");
			Input::addAxis("kb_k_l");
		}

	}
}