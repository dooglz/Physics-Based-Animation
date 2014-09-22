#pragma once
#include "renderer.h"

class Vector3;

class CGLut_Renderer:public CRenderer
{
public:

	// Basic Draw Functions (e.g., for lines, points )

	// Takes three paramaters, i.e., the start and end position in 3D
	// of the arrow position in the world, and the size of the arrow

	void DrawArrow(const Vector3& p0, const Vector3& p1, double D);

	// For simple displaying of lines - takes two 3D positions
	// start and end of the line in the 3D world
	void DrawLine(const Vector3& p0, const Vector3& p1);

	// Draw 3D spherical mesh in the environment
	// paramaters should be self explanitory (i.e., position, radius and colour)
	void DrawSphere(const Vector3& p0, float radius, float r, float g, float b);

	Vector3 GetMousePosition2Dto3D();

	void PrepForRender();
	void FinishRender();
	void createWindow(){};
};