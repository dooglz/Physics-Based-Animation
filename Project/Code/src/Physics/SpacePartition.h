//Creates and manages the spacial partition, also used for returning a list of near objects
#pragma once
#include "../Engine/Maths.h"
#include <vector>

#define DIMENSTIONS 2
#define BOXSIZE 10.0f
#define WORLDSIZE 150.0f
#define ORIGIN Vector3(-(WORLDSIZE / 2.0f),0,-(WORLDSIZE / 2.0f))
#define LENGTH (int)(WORLDSIZE / BOXSIZE)

namespace Physics{
	class CPhysicsObject;

	class CSpacePartition
	{
	protected:
		static void getSpace(const Vector3& Position, unsigned int &X, unsigned int &Z, unsigned int &Y);
#if ( DIMENSTIONS ==2)
		static std::vector<CPhysicsObject*>* _theGrid[LENGTH][LENGTH];
#elif (DIMENSTIONS == 3)
		static std::vector<CPhysicsObject*>* _theGrid[LENGTH][LENGTH][LENGTH];
#endif

	public:
		static std::vector<CPhysicsObject*>* getSpace(const Vector3& Position);
		static std::vector<CPhysicsObject*>** getSurroundingSpaces(const Vector3& Position);
		static void Register(CPhysicsObject* const obj);
		static void Remove(const CPhysicsObject& obj);
		static void Update();
	};

}