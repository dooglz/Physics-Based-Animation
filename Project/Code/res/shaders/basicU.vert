#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 LVertexPos2D;
// Output data ; will be interpolated for each fragment.
out vec4 fragmentColor;
// Values that stay constant for the whole mesh.
uniform mat4 MVP;

void main(){	

	// Output position of the vertex, in clip space : MVP * position
	gl_Position =  MVP * vec4(LVertexPos2D,1);
	//gl_Position = vec4(LVertexPos2D,1);

	// The color of each vertex will be interpolated
	// to produce the color of each fragment
	//fragmentColor = vertexColor;
	fragmentColor = vec4(1.0, 0.3, 0.2,1.0);
}
