#pragma once
namespace Engine{
	//Should really be called physicsInterface.
	class Physics{

	protected:

	public:
		static void Init();
		static void Tick(unsigned long t, unsigned long  timeStep);
		static void Shutdown();
	};
}