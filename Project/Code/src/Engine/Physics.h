#pragma once
namespace Engine{
	//Should really be called physicsInterface.
	class Physics{

	protected:

	public:
		static void Init();
		static void Tick(double t, double timeStep);
		static void Shutdown();
	};
}