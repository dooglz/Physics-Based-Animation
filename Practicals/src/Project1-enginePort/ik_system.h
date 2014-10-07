#pragma once
#include "sharp-blue/Mesh.h"
#include "sharp-blue/GMaths.h"

namespace Engine{
	class Actor;
}

class CIkLink
{
public:
	CIkLink(Vector3& axis, float angle);

	// Note- we could store this as a quaternion
	Vector3	m_axis;		// local axis
	// local angle, in Radians
	float m_angle;	

	float linkLength;

	// base of link position and orientation
	Matrix4	m_base;

	Engine::Actor* actor;
	Engine::Actor* actor2;
};

class CIkSystem
{
public:
	std::vector<CIkLink*> links;
	// Simulation constants
	int	numLinks = 3;
	
	// Build or set of links (i.e., length and angle)
	void Setup();
	//only move one link at at time for now
	void Reach(int i, const Vector3& target);
	void UpdateHiearchy();
	void Update(float delta);

	// Graphics/Render update code
	void Render();

};
