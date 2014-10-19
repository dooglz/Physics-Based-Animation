#pragma once
namespace Engine{

	class Platform;
	class Scene;
	class Engine
	{
	protected:
		static bool _running;
		static Platform* _platform;
		static Scene* _scene;

	public:
		Engine();
		static void Init();
		static void createwindow();

		static void Update(double delta);
		static void Render();

		static bool Run();
		static void Shutdown();

	private:

	};
}
