#pragma once
#include "sharp-blue/Mesh.h"
#include "sharp-blue/GMaths.h"
namespace Engine{
	class Actor;
}
class CIkLink
{
public:
	CIkLink(vector3& axis, float angle);

	// Note- we could store this as a quaternion
	vector3	m_axis;		// local axis
	float m_angle;	// local angle

	float linkLength;

	// base of link position and orientation
	matrix4	m_base;

	Engine::Actor* actor;
};

class CIkSystem
{
public:
	std::vector<CIkLink*> links;
	// Simulation constants
	int	numLinks = 7;
	
	// Build or set of links (i.e., length and angle)
	void Setup();
	//only move one link at at time for now
	void Reach(int i, const vector3& target);
	void UpdateHiearchy();
	void UpdateIK();

	void Update(float delta);

	// Graphics/Render update code
	void Render();
	static void DrawSphere(const vector3& p0, float radius, float r, float g, float b);

};
