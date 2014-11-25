#pragma once
#include "platform.h"

namespace Engine{
	namespace PS3{
		class PS3_Platform : public CPlatform
		{
		private:

		protected:
			static bool _running;
		public:
			PS3_Platform();
			void Init();
			void createwindow();
			void Shutdown();

			void SaveFile(const std::string& name){};
		};
	}
}
