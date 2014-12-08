#include "Cm_FpsMotor.h"
#include "Engine/Input.h"
#include "glm/gtc/matrix_access.hpp"
#include "Engine/Entity.h"

static Vector3 cameraPos;
static float horizontalAngle;
static float verticalAngle;
Matrix4 oviewMatrix;

CmFpsMotor::CmFpsMotor() : Engine::CComponent("FpsMotor")
{
	horizontalAngle = 1.5f;
	cameraPos = Vector3(-30, 2.5, 0);
	verticalAngle = 0.0f;
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

	const float speed = 1.0f * delta;
	const float hRotSpeed = 0.05f *speed;
	const float vRotSpeed = 0.035f *speed;
	Vector3 rot = Vector3(0);

	{
		const Vector3 UP = Vector3(0, 1.0f, 0);
		const Vector3 RIGHT = Vector3(0, 0, 1.0f);
		const Vector3 FORWARD = Vector3(1.0f, 0, 0);

		//ijklUO world translate RCS-like movement, 
		if (Engine::Input::getMapData("J") > 128){
			rot += -RIGHT;
		}
		if (Engine::Input::getMapData("L") > 128){
			rot += RIGHT;
		}
		if (Engine::Input::getMapData("K") > 128){
			rot += FORWARD;
		}
		if (Engine::Input::getMapData("I") > 128){
			rot += -FORWARD;
		}
		if (Engine::Input::getMapData("U") > 128){
			rot += UP;
		}
		if (Engine::Input::getMapData("O") > 128){
			rot += -UP;
		}
		Ent->setPosition(Ent->getPosition() + rot*speed);

		//pitch
		if (Engine::Input::getMapData("down") > 128){

			

			Ent->setRotation(AngleAxisToQuat(Rotate(Inverse(Ent->getRotation()), FORWARD), vRotSpeed) * Ent->getRotation());
			verticalAngle -= 0.01f;
		}
		if (Engine::Input::getMapData("up") > 128){
			// Ent->setRotation(AngleAxisToQuat(FORWARD*Inverse(Ent->getRotation()), -vRotSpeed) * Ent->getRotation());
			Ent->setRotation(AngleAxisToQuat(Rotate(Inverse(Ent->getRotation()), FORWARD), -vRotSpeed) * Ent->getRotation());
			verticalAngle += 0.01f;
		}

		//yaw
		if (Engine::Input::getMapData("left") > 128){
			Ent->setRotation(AngleAxisToQuat(UP, hRotSpeed) * Ent->getRotation());
			horizontalAngle += 0.01f;
		}
		if (Engine::Input::getMapData("right") > 128){
			Ent->setRotation(AngleAxisToQuat(UP, -hRotSpeed) * Ent->getRotation());
			horizontalAngle -= 0.01f;
		}	
	}
	Ent->setRotation(Normalize(Ent->getRotation()));

	Vector3 right = GetRightVector(Ent->getRotation());
	Vector3 direction  = GetForwardVector(Ent->getRotation());

#if defined _PS3_
	// Direction : Spherical coordinates to Cartesian coordinates conversion
	direction = Vector3(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
		);

	// Right vector
	right = Vector3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
		);

	// Up vector
	Vector3 up = Cross(right, direction);

#endif

	//First person fly camera movement
	rot = Vector3(0);
	if (Engine::Input::getMapData("D") > 128){
		//cameraPos += (speed)* right;
		rot -= (speed)* right;
	}
	if (Engine::Input::getMapData("A") > 128){
		//cameraPos += (speed)* right;
		rot += (speed)* right;
	}
	if (Engine::Input::getMapData("S") > 128){
		//cameraPos += (speed)*direction;
		rot -= (speed)*direction;
	}
	if (Engine::Input::getMapData("W") > 128){
	//	cameraPos += (speed)*direction;
		rot += (speed)*direction;
	}
	Ent->setPosition(Ent->getPosition() + rot);

#if defined _PS3_
	oviewMatrix = lookat(cameraPos, cameraPos + direction, up);
#endif

}