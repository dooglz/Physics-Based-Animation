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
		CIkLink* L = new CIkLink(Vector3(0, 0, 1), (float)i*10.0f);
		L->actor = new CPrimative(SPHERE);
		L->linkLength = 2.0f;
		links.push_back(L);
	}
}

void CIkSystem::Reach(int i, const Vector3& target)
{
	// Get the location of the current end-effector
	Vector3 end = M4::Transform(links[links.size() - 1]->m_base, Vector3(links[links.size() - 1]->linkLength, 0, 0));
	Vector3 dir = target - M4::GetTranslation(links[i]->m_base);
	
	Vector3 vB = MatrixToEuler(links[i]->m_base);
	Vector3 v0 = (end - vB);
	Vector3 v1 = Normalize(target - vB);
	
	Vector3 axis = glm::cross(end - vB, v1);
	ASSERT( axis.length()>0 );
	axis = Normalize(axis);

	Vector3 axv = Vector3(end - vB);
	float ax = Dot(v0, v1) / axv.length();
	ax = fmin(1.0f, fmax(ax, -1.0f));
	ax = (float)acos(ax);

	glm::quat q;

	// We have the delta axis-angle- and we know the links current
	// axis-angle - we use quaternions to adjust the current axis
	// angle (i.e., quaternions are more efficient - easier to find the
	// shortest path)

	Quaternion qCur = AngleAxisToQuat(links[i]->m_axis, links[i]->m_angle);
	Quaternion qDif = AngleAxisToQuat(axis, -ax);

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
	links[i]->m_axis = axis2;
	links[i]->m_angle = angle2;
}


void CIkSystem::UpdateHiearchy()
{
	//links[0]->m_base = SetTranslation( Vector3(0,0,0) ); 
	for (int i = 0; i<(int)links.size(); ++i)
	{
		Matrix4 R1 = AngleAxisToMatrix(links[i]->m_axis, links[i]->m_angle * (M_PI / 180.0f));
		Matrix4 T1 = M4::translation(Vector3(links[i]->linkLength, 0, 0));
		links[i]->m_base = R1 * T1;
		if (i > 0) links[i]->m_base = links[i]->m_base * links[i - 1]->m_base;
	}
}

// Graphics/Render update code
void CIkSystem::Render()
{
	for (int i = 0; i < (int)links.size(); ++i)
	{
		links[i]->actor->Render();
	}
}

void CIkSystem::Update(float delta)
{
	// Current `end' effector position
	//Vector3 target = Renderer.GetMousePosition2Dto3D();
	Vector3 target = Vector3{ 5.0f, 6.0f, 0 };
	//Renderer.DrawSphere(target, 0.16f, 0.1f, 0.5f, 0.4f);

	// Either work from the end towards the base or from the
	// base towards the leaf
	//for (int i=links.size()-1; i>=0; --i)
	for (int i = 0; i<(int)links.size(); i++)
	{
		// Update the whole hiearchy - however, we can optimize this
		// to only update the section of the hierarchy or update the target
		// based on the modified link transformation
		UpdateHiearchy();

		// We iteratively update the `target' based on
		// the new position of the limb - so we don't have
		// to keep updating the hierarchy - performance
		// improvement 
	//	Reach(i, target);
	}

	for (int i = 0; i<(int)links.size(); ++i)
	{
		//	Renderer.DrawSphere(GetTranslation(links[i]->m_base), 0.1f, 0.5f, 0.5f, 0.9f);
		Vector3 base = M4::GetTranslation(links[i]->m_base);
		Vector3 end = M4::Transform(links[i]->m_base, Vector3(links[i]->linkLength, 0, 0));
		links[i]->actor->position = base;
		//links[i]->actor->rotation = AngleAxisToEuler(links[i]->m_axis, links[i]->m_angle);
		//	Renderer.DrawArrow(base, end, 0.2f);
	}

}