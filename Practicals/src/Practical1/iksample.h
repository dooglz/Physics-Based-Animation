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

class Link
{
public:
	Link(Vector3& axis, float angle);
	// Note- we could store this as a quaternion
	Vector3	m_axis;		// local axis
	float		m_angle;	// local angle

	// base of link position and orientation
	Matrix4	m_base;
};

class CIkSystem
{
public:
	std::vector<Link*>	links;
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

// Basic Draw Functions (e.g., for lines, points )

// Takes three paramaters, i.e., the start and end position in 3D
// of the arrow position in the world, and the size of the arrow

void DrawArrow(const Vector3& p0, const Vector3& p1, GLdouble D);

// For simple displaying of lines - takes two 3D positions
// start and end of the line in the 3D world
void DrawLine(const Vector3& p0, const Vector3& p1);

// Draw 3D spherical mesh in the environment
// paramaters should be self explanitory (i.e., position, radius and colour)
void DrawSphere(const Vector3& p0, float radius, float r, float g, float b);

Vector3 GetMousePosition2Dto3D();
