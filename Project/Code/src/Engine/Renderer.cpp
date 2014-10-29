#include "Renderer.h"

namespace Engine
{
	CRenderer* Renderer = NULL;

	void CRenderer::SetViewMatrix(Matrix4 vm)
	{
		_viewMat = vm;
	}

}