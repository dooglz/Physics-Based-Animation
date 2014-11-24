#pragma once

class Game{

protected:
	bool _running;
	void registerInputs();
public:
	Game();
	void Init();
	void Update(double delta);
	bool Run(){ return _running; }
	void Shutdown();
};