#include "ik_Demo.h"
#include "ik_system.h"
#include <string>

#include "sharp-blue/GMaths.h"
#include "sharp-blue/Mesh.h"
#include "sharp-blue/torus.h"
#include "sharp-blue/Input.h"
#include "sharp-blue/Actor.h"
#include "sharp-blue/GameEngine.h"	
#include "sharp-blue/Renderer.h"
#include "sharp-blue/MeshLoader.h"
#include "sharp-blue/Event_Manager.h"
#include "sharp-blue/Font.h"

Matrix4 ViewProjection;
Matrix4 ModelProjection1;
Matrix4 ModelProjection2;

stMesh* cubeMesh;
Vector3 cameraPos;

CIkSystem Isystem;

float horizontalAngle;
float verticalAngle;

void registerInputs()
{
	//Todo: read these from file
	//using pushback rather than a={...} as the ps3 compiler is old and dumb

	std::vector<std::string> a;

	a.push_back("kb_space"); a.push_back("gp_1_start"); a.push_back("ms_l");
	Engine::Input::addMap("action1", a);
	a.clear();

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


void CIK_Demo::init()
{
	//load a model from a .obj file
	std::string name = "models/cube.obj";
	name = FILE_PATH + name;
	cubeMesh = Engine::GameEngine::Meshloader->loadOBJFile(name);
	Engine::GameEngine::Renderer->assignShader(cubeMesh, "");
	Engine::GameEngine::Meshloader->loadOnGPU(cubeMesh);

	//Setup view matrices
	//Projection matrix : 60° Field of View, 16:9 ratio, display range : 0.1 unit <-> 100 units
	Engine::GameEngine::Renderer->projMatrix = M4::perspective(60.0f, (16.0f / 9.0f), 1.0f, 2000.0f);

	registerInputs();

	horizontalAngle = 3.0f;
	cameraPos = Vector3(0, 0, 30.0f);
	verticalAngle = 0.0f;

	Isystem.Setup();
}

float a;
float x, y, z;
void CIK_Demo::update(float delta)
{
	a += delta;

	Isystem.Update(delta);

	if (Engine::Input::getMapData("action1") > 128){
		printf("action pressed\n");
	}
	if (Engine::Input::getMapData("left") > 128){
		horizontalAngle += 0.01f;
	}
	if (Engine::Input::getMapData("right") > 128){
		horizontalAngle -= 0.01f;
	}
	if (Engine::Input::getMapData("up") > 128){
		verticalAngle += 0.01f;
	}
	if (Engine::Input::getMapData("down") > 128){
		verticalAngle -= 0.01f;
	}

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	Vector3 direction = Vector3(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
		);

	// Right vector
	Vector3 right = Vector3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
		);

	// Up vector
	Vector3 up = M3::cross(right, direction);

	if (Engine::Input::getMapData("W") > 128){
		cameraPos += (delta / 10.0f)*direction;
	}
	if (Engine::Input::getMapData("A") > 128){
		cameraPos += (delta / -10.0f)* right;
	}
	if (Engine::Input::getMapData("S") > 128){
		cameraPos += (delta / -10.0f)*direction;
	}
	if (Engine::Input::getMapData("D") > 128){
		cameraPos += (delta / 10.0f)* right;
	}

	Engine::GameEngine::Renderer->viewMatrix = M4::lookat(cameraPos, cameraPos + direction, up);

	Matrix4 rot = M4::rotation(a*0.025f, Vector3(0, 1, 0));
	Matrix4 rot2 = M4::rotation(a*-0.01f, Vector3(0, 1, 0));
	Matrix4 scl = M4::scale(Vector3(2.0f, 2.0f, 2.0f));
	//glm rotation uses degrees
	ModelProjection1 = ViewProjection * M4::translation(Vector3(0, 0, 0))* scl * rot2;
	ModelProjection2 = ViewProjection * M4::translation(Vector3(0, 0, 0))* scl * rot;
}


void CIK_Demo::render()
{
	Isystem.Render();
}

void CIK_Demo::shutdown()
{

}

