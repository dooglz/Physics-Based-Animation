#include "Cm_FpsMotor.h"
#include "Engine/Input.h"
#include "glm/gtc/matrix_access.hpp"
#include "Engine/Entity.h"

CmFpsMotor::CmFpsMotor() : Engine::CComponent("FpsMotor")
{
	registerInputs();
}

void CmFpsMotor::registerInputs()
{
	std::vector<std::string> a;
	a.push_back("kb_left"); a.push_back("gp_1_x");
	Engine::Input::addMap("left", a);
	a.clear();
	a.push_back("kb_right"); a.push_back("gp_1_b");
	Engine::Input::addMap("right", a);
	a.clear();
	a.push_back("kb_up"); a.push_back("gp_1_y");
	Engine::Input::addMap("up", a);
	a.clear();
	a.push_back("kb_down"); a.push_back("gp_1_a");
	Engine::Input::addMap("down", a);
	a.clear();

	a.push_back("kb_k_i"); 
	Engine::Input::addMap("I", a);
	a.clear();
	a.push_back("kb_k_k");
	Engine::Input::addMap("K", a);
	a.clear();
	a.push_back("kb_k_j");
	Engine::Input::addMap("J", a);
	a.clear();
	a.push_back("kb_k_l");
	Engine::Input::addMap("L", a);
	a.clear();

	a.push_back("kb_k_w"); a.push_back("gp_1_dpad_u");
	Engine::Input::addMap("W", a);
	a.clear();
	a.push_back("kb_k_a"); a.push_back("gp_1_dpad_l");
	Engine::Input::addMap("A", a);
	a.clear();
	a.push_back("kb_k_s"); a.push_back("gp_1_dpad_d");
	Engine::Input::addMap("S", a);
	a.clear();
	a.push_back("kb_k_d"); a.push_back("gp_1_dpad_r");
	Engine::Input::addMap("D", a);
	a.clear();
}

void CmFpsMotor::Update(double delta)
{
	Vector3 rot = Vector3(0);
	if (Engine::Input::getMapData("down") > 128){
		rot += Vector3(1.0f, 0, 0);
	}
	if (Engine::Input::getMapData("up") > 128){
		rot += Vector3(-1.0f, 0, 0);
	}
	Ent->setRotation( Normalize(Ent->getRotation() * AngleAxisToQuat(rot, 20.0f*(float)delta)));
	rot = Vector3(0);
	if (Engine::Input::getMapData("left") > 128){
		rot += Vector3(0, 1.0f, 0);
	}
	if (Engine::Input::getMapData("right") > 128){
		rot += Vector3(0, -1.0f, 0);
	}	
	Ent->setRotation(Normalize(Ent->getRotation() * AngleAxisToQuat(rot, 20.0f*(float)delta)));

	//ijkl
	rot = Vector3(0);
	if (Engine::Input::getMapData("J") > 128){
		rot += Vector3(-1.0f, 0, 0);
	}
	if (Engine::Input::getMapData("L") > 128){
		rot += Vector3(1.0f, 0, 0);
	}
	if (Engine::Input::getMapData("K") > 128){
		rot += Vector3(0, 0, 1.0f);
	}
	if (Engine::Input::getMapData("I") > 128){
		rot += Vector3(0, 0, -1.0f);
	}
	Ent->setPosition(Ent->getPosition() + rot*40.0f*(float)delta);

	//wasd
	rot = Vector3(0);
	if (Engine::Input::getMapData("D") > 128){
		Vector3 right = Vector3(glm::column(Ent->getTranform(), 0));
		rot += right;
	}
	if (Engine::Input::getMapData("A") > 128){
		Vector3 right = Vector3(glm::column(Ent->getTranform(), 0));
		rot += -1.0f*right;
	}
	if (Engine::Input::getMapData("S") > 128){
		Vector3 forward = Vector3(glm::column(Ent->getTranform(), 2));
		rot += forward;
	}
	if (Engine::Input::getMapData("W") > 128){
		Vector3 forward = Vector3(glm::column(Ent->getTranform(), 2));
		rot += -1.0f*forward;
	}
	Ent->setPosition(Ent->getPosition() + rot*20.0f*(float)delta);

}