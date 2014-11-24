#pragma once
// BaseClass for platform specific code
namespace Engine{
	class CPlatform
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
		CPlatform(){};
		virtual void Init() = 0;
		virtual void createwindow() = 0;
		virtual void Shutdown() = 0;
		virtual void SaveFile(const std::string& name) = 0;
		static unsigned short GetSreenWidth(){ return _screenWidth; }
		static unsigned short GetSreenHeight(){ return  _screenHeight; }
	};

	extern CPlatform* Platform;
}
