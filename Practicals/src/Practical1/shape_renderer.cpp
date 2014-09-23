#include "shape_Renderer.h"
#include "utilities.h"
#include "sdl/SDL.h"
#include "glew/glew.h"
#include <vector>
#include "helpermath.h" // Vector3, Matrix4, and Quaternion
extern void CheckGL();

struct Vertex
{
	float x, y, z;
	unsigned int rgba;
};

struct Mesh{
	bool loadedMain;
	bool loadedLocal;
	int numVerts;
	bool strip;
	bool fan;
	bool line;
	// mesh data in main memory
	std::vector<Vertex> vertexData;
	std::vector<unsigned int > indices;

	//! A reference to the shader program to use
	//Engine::OGL::OGL_ShaderProgram * program;
	unsigned int gVBO;
	unsigned int gVAO;
	unsigned int gIBO;

};

const Vertex arrow_points[5] = { { 1, 1, -1, 0 }, { 1, -1, -1, 0 }, { -1, -1, -1, 0 }, { -1, 1, -1, 0 }, { 0, 0, 1, 0 } };
const unsigned int arrow_indices[18] = { 0, 4, 1, 1, 4, 2, 2, 4, 3, 3, 4, 0, 0, 1, 2, 0, 3, 2 };

const Vertex Square_points[8] = { { 1, 1, -1, 0 }, { 1, -1, -1, 0 }, { -1, -1, -1, 0 }, { -1, 1, -1, 0 },
								{ 1, 1, 1, 0 }, { 1, -1, 1, 0 }, { -1, -1, 1, 0 }, { -1, 1, 1, 0 } };
const unsigned int Square_indices[18] = { 0, 1, 2, 0, 3, 2, 4, 5, 6, 4, 7, 6, 0, 4, 5, 2, 5, 6 };

Mesh square;
Mesh arrow;
void CShape_Renderer::Init(){
	arrow.vertexData.insert(arrow.vertexData.end(), &arrow_points[0], &arrow_points[5]);
	arrow.indices.insert(arrow.indices.end(), &arrow_indices[0], &arrow_indices[5]);
	arrow.numVerts = 5;
	LoadOnGPU(&arrow);
}

void CShape_Renderer::DrawArrow(const Vector3& p0, const Vector3& p1, double D)
{
	RenderMesh(&arrow, Matrix4::Identity());
}

// For simple displaying of lines - takes two 3D positions
// start and end of the line in the 3D world
void CShape_Renderer::DrawLine(const Vector3& p0, const Vector3& p1)
{
	RenderMesh(&arrow, Matrix4::Identity());
}

// Draw 3D spherical mesh in the environment
// paramaters should be self explanitory (i.e., position, radius and colour)
void CShape_Renderer::DrawSphere(const Vector3& p0, float radius, float r, float g, float b)
{
	RenderMesh(&arrow, Matrix4::Identity());
}



void CShape_Renderer::LoadOnGPU(Mesh* msh)
{
	//Generate VAO
	glGenVertexArrays(1, &msh->gVAO);
	CheckGL();
	
	//Bind VAO
	glBindVertexArray(msh->gVAO);
	CheckGL();

	//vertex vbo-------
	//Generate VBO
	glGenBuffers(1, &(msh->gVBO));
	CheckGL();

	//Bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, (msh->gVBO));
	CheckGL();

	//put the data in it
	glBufferData(GL_ARRAY_BUFFER, msh->vertexData.size() * sizeof(Vertex), &msh->vertexData[0], GL_STATIC_DRAW);
	CheckGL();

	/* stVertex layout:
	[x,y,z,color]
	[float,float,float,uint]
	Color is really 4 chars [rgba]
	So effectivly, this is what ogl will see:
	[float,float,float,char,char,char,char]
	*/
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,		//index
		3,		//size
		GL_FLOAT,	//type
		GL_FALSE,	//normalised
		sizeof(Vertex),	//stride
		NULL	//pointer/offset
		);
	CheckGL();

	//color data
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,	//index
		4,	//size
		GL_UNSIGNED_BYTE,	//type
		GL_TRUE,	//normalised
		sizeof(Vertex),	//stride
		(void*)(sizeof(float) * 3)	//pointer/offset
		);
	CheckGL();

	//Unblind VBO
	glBindVertexArray(NULL);
	CheckGL();

	//index  vbo --------

	//Generate IBO
	glGenBuffers(1, &(msh->gIBO));
	CheckGL();

	//Bind IBO
	glBindBuffer(GL_ARRAY_BUFFER, (msh->gIBO));
	CheckGL();

	//put the data in it
	glBufferData(GL_ARRAY_BUFFER, msh->indices.size() * sizeof(unsigned int), &msh->indices[0], GL_STATIC_DRAW);
	CheckGL();

	//Unblind VAO
	glEnableVertexAttribArray(NULL);
	CheckGL();


	msh->loadedLocal = true;
}


void CShape_Renderer::RenderMesh(Mesh* msh, Matrix4 mvp)
{
	/*
	glUseProgram(msh->program->getID());
	OGL_Renderer::checkerr();

	//get shader input indexes
	GLint mvpIn = glGetUniformLocation(msh->program->getID(), "MVP");
	OGL_Renderer::checkerr();

	//Send MVP
	glUniformMatrix4fv(mvpIn, 1, false, glm::value_ptr(mvp));
	OGL_Renderer::checkerr();

	//Bind to VAO
	glBindVertexArray(msh->gVAO);
	OGL_Renderer::checkerr();

	//DRAW
	if (msh->line == true){
		if (msh->strip == true){
			glDrawArrays(GL_LINE_STRIP, 0, msh->numVerts);
		}
		else{
			glDrawArrays(GL_LINES, 0, msh->numVerts);
		}
	}
	else{
		if (msh->fan == true){
			glDrawArrays(GL_TRIANGLE_FAN, 0, msh->numVerts);
		}
		else if (msh->strip == true){
			glDrawArrays(GL_TRIANGLE_STRIP, 0, msh->numVerts);
		}
		else{
			glDrawArrays(GL_TRIANGLES, 0, msh->numVerts);
		}
	}
	OGL_Renderer::checkerr();

	//unbind VAO
	glBindVertexArray(0);
	OGL_Renderer::checkerr();

	//Unbind program
	glUseProgram(NULL);
	OGL_Renderer::checkerr();

	*/

	glDrawElements(GL_TRIANGLES, msh->indices.size(),GL_UNSIGNED_INT, (void*)0);
};