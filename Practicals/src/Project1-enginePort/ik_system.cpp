/*
Uncomplicated IK Simulation Tutorial

Minimilistic sample program - for educational purposes - it should
be straightforward to follow through, dissect and understand, so that you are
able to expand and incorporate the solution into your own program

www.napier.ac.uk/games/

b.kenwright@napier.ac.uk
*/
#include "ik_system.h"
#include "sharp-blue/Renderer.h"
#include "sharp-blue/GameEngine.h"	
#include "sharp-blue/GMaths.h"
#include "primative_actor.h"
#include "sharp-blue/Actor.h"

Vector3 t1;
Engine::Actor targetPoint;
extern stMesh* cubeMesh;

CIkLink::CIkLink(Vector3& axis, float angle)
{
	m_axis = axis;
	m_angle = angle;
}


// Build or set of links (i.e., length and angle)
void CIkSystem::Setup()
{
	for (int i = 0; i<numLinks; ++i)
	{
		//if (i > 0) { rot = (float)i*0.1f; }
		CIkLink* L = new CIkLink(Vector3(0, 0, 1), (float)i*0.0f);
		L->m_base = Matrix4(1.0f);

		L->actor = new CPrimative(SPHERE);
		L->actor2 = new CPrimative(SPHERE);
		L->linkLength = 4.0f;
		links.push_back(L);
	}
	targetPoint = Engine::Actor();
	targetPoint.scale = Vector3(1.0f, 1.0f, 1.0f);
	targetPoint.rotation = Vector3(0, 0, 0);
	targetPoint.Mesh = cubeMesh;
}

void CIkSystem::Reach(int i, const Vector3& target)
{
	// Get the location of the current end-effector
	Vector3 end = M4::Transform(links[links.size() - 1]->m_base, Vector3(links[links.size() - 1]->linkLength, 0, 0));

	glm::vec4 v4(Vector3(links[links.size() - 1]->linkLength, 0, 0), 1.0f);
	glm::vec4 t = links[links.size() - 1]->m_base * v4;
	end = Vector3(t.x, t.y, t.z);


	Vector3 dir = target - M4::GetTranslation(links[i]->m_base);
	
	Vector3 vB = MatrixToEuler(links[i]->m_base);
	Vector3 v0 = Normalize(end - vB);
	Vector3 v1 = Normalize(target - vB);
	
	Vector3 axis = glm::cross(end - vB, v1);
	bool b = abs(axis.x) == 0 && abs(axis.y) == 0 && abs(axis.z) == 0;
	//ASSERT( !b );
	if (b){
		axis = Vector3(0, 0, 1);
	}
	axis = Normalize(axis);

	//Vector3 axv = Vector3(end - vB);
	
	//float l = v0.length();
	float dot = Dot(v0, v1);
	float ax = dot;
	ax = fmin(1.0f, fmax(ax, -1.0f));
	ax = (float)acos(ax);// *M_PI / 180.0f;

	glm::quat q;

	// We have the delta axis-angle- and we know the links current
	// axis-angle - we use quaternions to adjust the current axis
	// angle (i.e., quaternions are more efficient - easier to find the
	// shortest path)

	Quaternion qCur = AngleAxisToQuat(links[i]->m_axis, links[i]->m_angle);
	Quaternion qDif = AngleAxisToQuat(axis, ax);

	Quaternion qNew = qCur * qDif;

	// Use slerp to avoid `snapping' to the target - if 
	// we instead want to `gradually' interpolate to 
	// towards the target
	//qNew = Slerp( qCur, qNew, 0.01f );

	// For 3D ball joint - we use an axis-angle combination
	// could just store a quaternion
	Vector3 axis2;
	float angle2;
	QuatToAngleAxis(qNew, axis2, angle2);
	links[i]->m_axis = Normalize(axis2);
	links[i]->m_angle = angle2;
}


void CIkSystem::UpdateHiearchy()
{
	//links[0]->m_base = SetTranslation( Vector3(0,0,0) ); 
	for (int i = 0; i<(int)links.size(); ++i)
	{
		Matrix4 R1 = AngleAxisToMatrix(links[i]->m_axis, links[i]->m_angle);
		Matrix4 T1 = M4::translation(Vector3(links[i]->linkLength, 0, 0));
		links[i]->m_base = T1*R1;
		if (i > 0){ 
			links[i]->m_base = links[i - 1]->m_base * links[i]->m_base;
		}
	//	printf("I'm Link %i,My rotation is: %f, my base is at: (%f,%f)\n", i, links[i]->m_angle, links[i]->m_base[3].x, links[i]->m_base[3].y);
	}
}

// Graphics/Render update code
void CIkSystem::Render()
{
	targetPoint.Render();
	for (int i = 0; i < (int)links.size(); ++i)
	{
		links[i]->actor->Render();
		links[i]->actor2->Render();
	}
}
float abb = 0.0f;
void CIkSystem::Update(float delta)
{
	abb += delta*0.005f;
	// Current `end' effector position
	//Vector3 target = Renderer.GetMousePosition2Dto3D();
	Vector3 target = Vector3{ 15.0f*sin(abb), 15.0f*cos(abb), 0 };
	//Vector3 target = Vector3{ 10.0f, 0.1f, 0 };
	targetPoint.position = target;
	targetPoint.rotation = Vector3{ abb, 0, 0 };

	printf("%f,%f \n", target.x, target.y);
	//Renderer.DrawSphere(target, 0.16f, 0.1f, 0.5f, 0.4f);

	// Either work from the end towards the base or from the
	// base towards the leaf
	for (int i=links.size()-1; i>=0; --i)
	//for (int i = 0; i<(int)links.size(); i++)
	{
		// Update the whole hiearchy - however, we can optimize this
		// to only update the section of the hierarchy or update the target
		// based on the modified link transformation
		UpdateHiearchy();

		// We iteratively update the `target' based on
		// the new position of the limb - so we don't have
		// to keep updating the hierarchy - performance
		// improvement 
		Reach(i, target);
	}

	for (int i = 0; i<(int)links.size(); ++i)
	{
		//	Renderer.DrawSphere(GetTranslation(links[i]->m_base), 0.1f, 0.5f, 0.5f, 0.9f);
		Vector3 base = M4::GetTranslation(links[i]->m_base);
		//Vector3 end = M4::Transform(links[i]->m_base, Vector3(links[i]->linkLength, 0, 0));
		glm::vec4 v(Vector3(links[i]->linkLength, 0, 0), 1.0f);
		Vector3 end = Vector3(links[i]->m_base * v);

		links[i]->actor->position = base;
		links[i]->actor2->position = end;

		//Vector3 rot = AngleAxisToEuler(links[i]->m_axis, links[i]->m_angle);

		Matrix3 m3 = Matrix3(links[i]->m_base);
		Quaternion q = glm::quat_cast(m3);
		Vector3 rot = QuatToEuler(q);
		//links[i]->actor->rotation = (rot);
		//return;
		//	Renderer.DrawArrow(base, end, 0.2f);
	}

}