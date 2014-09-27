#include "primative_actor.h"
//#include "Asteroid_Shape_Generator.h"
#include "sharp-blue/GameEngine.h"	
#include "sharp-blue/Renderer.h"	

extern stMesh* cubeMesh;

CPrimative::CPrimative(stPrimitive_type type){
	switch (type)
	{
	case CUBE:
		Mesh = cubeMesh;
		break;
	default:
		Mesh = cubeMesh;
		break;
	}
	
	scale = vector3(1, 1, 1);
	rotation = vector3(0, 0, 0);
	//printf("new asteroid: %i -  %f,%f,%f - %f,%f\n", shape, a, b, c, _direction.x, _direction.y);
}


void CPrimative::update(float delta){

}

void CPrimative::render(){

}
