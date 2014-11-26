#include "Renderer.h"

namespace Engine
{
	CRenderer* Renderer = NULL;

	void CRenderer::SetViewMatrix(const Matrix4& vm)
	{
		_viewMat = vm;
	
		_viewprojectionMat = _projectionMat * _viewMat;
		aap = V4toV3(Column(vm, 3));
		aan = Normalize(V4toV3(Column(_viewprojectionMat, 3)));
	}

	CRenderer::CRenderer(){
		_projectionMat = Perspective((float)(60.0f*(M_PI / 180.0f)), (16.0f / 9.0f), 1.0f, 2000.0f);
		//print(_projectionMat);
	};

}