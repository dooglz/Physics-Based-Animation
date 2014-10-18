#pragma once
namespace Engine{
	class Engine
	{
	protected:
		static bool _running;
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
