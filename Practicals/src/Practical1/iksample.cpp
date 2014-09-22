/*
Uncomplicated IK Simulation Tutorial

Minimilistic sample program - for educational purposes - it should
be straightforward to follow through, dissect and understand, so that you are
able to expand and incorporate the solution into your own program

www.napier.ac.uk/games/

b.kenwright@napier.ac.uk
*/

#include "utilities.h"
#include "helpermath.h" // Vector3, Matrix4, and Quaternion
#include "iksample.h"
#include "glut_renderer.h"


extern CGLut_Renderer Renderer;

CLink::CLink(Vector3& axis, float angle)
{
	m_axis = axis;
	m_angle = angle;
}


// Build or set of links (i.e., length and angle)
void CIkSystem::Setup()
{
	for (int i = 0; i<numLinks; ++i)
	{
		links.push_back(new CLink(Vector3(0, 0, 1), (float)i*0.2f));
	}
}


void CIkSystem::Reach(int i, const Vector3& target)
{
	// Get the location of the current end-effector
	Vector3 end =
		Transform(links[links.size() - 1]->m_base, Vector3(linkLength, 0, 0));

	Vector3 dir = target - GetTranslation(links[i]->m_base);

	Vector3 vB = GetTranslation(links[i]->m_base);
	Vector3 v0 = (end - vB);
	Vector3 v1 = Normalize(target - vB);

	Vector3 axis = Cross(end - vB, v1);
	//DBG_ASSERT( axis.LengthSq()>0 );
	axis = Normalize(axis);
	
	float ax = Dot(v0, v1) / Length(end - vB);
	ax = fmin(1.0f, fmax(ax, -1.0f));
	ax = (float)acos(ax);

	// We have the delta axis-angle- and we know the links current
	// axis-angle - we use quaternions to adjust the current axis
	// angle (i.e., quaternions are more efficient - easier to find the
	// shortest path)
	Quaternion qCur = FromAxisAngle(links[i]->m_axis, links[i]->m_angle);

	Quaternion qDif = FromAxisAngle(axis, -ax);

	Quaternion qNew = qCur * qDif;

	// Use slerp to avoid `snapping' to the target - if 
	// we instead want to `gradually' interpolate to 
	// towards the target
	//qNew = Slerp( qCur, qNew, 0.01f );

	// For 3D ball joint - we use an axis-angle combination
	// could just store a quaternion
	Vector3 axis2;
	float angle2 = ToAxisAngle(qNew, axis2);
	links[i]->m_axis = axis2;
	links[i]->m_angle = angle2;
}


void CIkSystem::UpdateHiearchy()
{
	//links[0]->m_base = SetTranslation( Vector3(0,0,0) ); 
	for (int i = 0; i<(int)links.size(); ++i)
	{
		Matrix4 R1 = SetRotationAxis(links[i]->m_axis, links[i]->m_angle);
		Matrix4 T1 = SetTranslation(Vector3(linkLength, 0, 0));
		links[i]->m_base = R1 * T1;
		if (i > 0) links[i]->m_base = links[i]->m_base * links[i - 1]->m_base;
	}
}



// This is the heart of the program - this is what performs all the IK
// work - if we have a problem - it will typically be located within this
// function
void CIkSystem::UpdateIK()
{
	
	// Current `end' effector position
	Vector3 target = Renderer.GetMousePosition2Dto3D();

	Renderer.DrawSphere(target, 0.16f, 0.1f, 0.5f, 0.4f);

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
		Reach(i, target);
	}

	for (int i = 0; i<(int)links.size(); ++i)
	{
		Renderer.DrawSphere(GetTranslation(links[i]->m_base), 0.1f, 0.5f, 0.5f, 0.9f);

		Vector3 base = GetTranslation(links[i]->m_base);
		Vector3 end = Transform(links[i]->m_base, Vector3(linkLength, 0, 0));

		Renderer.DrawArrow(base, end, 0.2f);
	}
	
}// End UpdateIK(..)


// Graphics/Render update code
void CIkSystem::Render(void)
{
	// Update 
	UpdateIK();
}
