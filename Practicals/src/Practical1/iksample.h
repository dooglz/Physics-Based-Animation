#pragma once
/*
Uncomplicated IK Simulation Tutorial

Minimilistic sample program - for educational purposes - it should
be straightforward to follow through, dissect and understand, so that you are
able to expand and incorporate the solution into your own program

www.napier.ac.uk/games/

b.kenwright@napier.ac.uk
*/

#include <vector>		// vector list
#include "helpermath.h" // Vector3, Matrix4, and Quaternion

class CLink
{
public:
	CLink(Vector3& axis, float angle);
	// Note- we could store this as a quaternion
	Vector3	m_axis;		// local axis
	float m_angle;	// local angle

	// base of link position and orientation
	Matrix4	m_base;
};

class CIkSystem
{
public:
	std::vector<CLink*>	links;
	// Simulation constants
	int		numLinks = 7;
	float	linkLength = 2.0f;

	// Build or set of links (i.e., length and angle)
	void Setup();
	void Reach(int i, const Vector3& target);
	void UpdateHiearchy();
	void UpdateIK();

	// Graphics/Render update code
	void Render(void);
};
