#pragma once
// BaseClass for platform specific code
namespace Engine{
	class Platform
	{
	private:

	protected:
		//! Output screen Width, in pixels
		static unsigned short _screenWidth;

		//! Output screen Height, in pixels
		static unsigned short _screenHeight;

		//! Output screen ratio, width/height
		static float _screenRatio;

	public:
		Platform(){};
		virtual void Init() = 0;
		virtual void createwindow() = 0;
		virtual void Shutdown() = 0;

	};
}
