#pragma once
class Vector3;

class CRenderer
{
public:

	// Basic Draw Functions (e.g., for lines, points )

	// Takes three paramaters, i.e., the start and end position in 3D
	// of the arrow position in the world, and the size of the arrow
	virtual void DrawArrow(const Vector3& p0, const Vector3& p1, double D) = 0;

	// For simple displaying of lines - takes two 3D positions
	// start and end of the line in the 3D world
	virtual void DrawLine(const Vector3& p0, const Vector3& p1) = 0;

	// Draw 3D spherical mesh in the environment
	virtual void DrawSphere(const Vector3& p0, float radius, float r, float g, float b) = 0;

	virtual Vector3 GetMousePosition2Dto3D() = 0;

	virtual void PrepForRender() = 0;
	virtual void FinishRender() = 0;
	virtual void createWindow() = 0;
};