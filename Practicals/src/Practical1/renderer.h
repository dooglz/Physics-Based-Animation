#pragma once
class Vector3;

class CRenderer
{
public:
	virtual Vector3 GetMousePosition2Dto3D() = 0;

	virtual void PrepForRender() = 0;
	virtual void FinishRender() = 0;
	virtual void InitDisplay() = 0;
};