#pragma once
#include "sharp-blue/Mesh.h"
#include "sharp-blue/GMaths.h"

class CIkLink
{
public:
	CIkLink(vector3& axis, float angle);

	// Note- we could store this as a quaternion
	vector3	m_axis;		// local axis
	float m_angle;	// local angle

	float linkLength = 2.0f;

	// base of link position and orientation
	matrix4	m_base;

	stMesh* mesh;
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

	// Graphics/Render update code
	void Render(void);
};
