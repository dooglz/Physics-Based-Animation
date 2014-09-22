/*
Uncomplicated IK Simulation Tutorial

Minimilistic sample program - for educational purposes - it should
be straightforward to follow through, dissect and understand, so that you are
able to expand and incorporate the solution into your own program

www.napier.ac.uk/games/

b.kenwright@napier.ac.uk
*/
#include "windows.h"
#include "GL/glut.h"
#include "utilities.h"
#include "helpermath.h" // Vector3, Matrix4, and Quaternion
#include "iksample.h"
#define RADPERDEG 0.0174533

Link::Link(Vector3& axis, float angle)
{
	m_axis = axis;
	m_angle = angle;
}


// -------------------------------------------------------------------------

// Basic Draw Functions (e.g., for lines, points )

// Takes three paramaters, i.e., the start and end position in 3D
// of the arrow position in the world, and the size of the arrow

void DrawArrow(const Vector3& p0, const Vector3& p1, GLdouble D)
{
	double x = p1.x - p0.x;
	double y = p1.y - p0.y;
	double z = p1.z - p0.z;
	double L = sqrt(x*x + y*y + z*z);

	GLUquadricObj *quadObj;

	glPushMatrix();

	glTranslated(p0.x, p0.y, p0.z);

	if ((x != 0.) || (y != 0.)) {
		glRotated(atan2(y, x) / RADPERDEG, 0., 0., 1.);
		glRotated(atan2(sqrt(x*x + y*y), z) / RADPERDEG, 0., 1., 0.);
	}
	else if (z<0){
		glRotated(180, 1., 0., 0.);
	}

	glTranslatef(0, 0, L - 4 * D);

	quadObj = gluNewQuadric();
	gluQuadricDrawStyle(quadObj, GLU_LINE);
	gluQuadricNormals(quadObj, GLU_SMOOTH);
	gluCylinder(quadObj, 2 * D, 0.0, 4 * D, 32, 1);
	gluDeleteQuadric(quadObj);

	quadObj = gluNewQuadric();
	gluQuadricDrawStyle(quadObj, GLU_LINE);
	gluQuadricNormals(quadObj, GLU_SMOOTH);
	gluDisk(quadObj, 0.0, 2 * D, 32, 1);
	gluDeleteQuadric(quadObj);

	glTranslatef(0, 0, -L + 4 * D);

	quadObj = gluNewQuadric();
	gluQuadricDrawStyle(quadObj, GLU_LINE);
	gluQuadricNormals(quadObj, GLU_SMOOTH);
	gluCylinder(quadObj, D, D, L - 4 * D, 32, 1);
	gluDeleteQuadric(quadObj);

	quadObj = gluNewQuadric();
	gluQuadricDrawStyle(quadObj, GLU_LINE);
	gluQuadricNormals(quadObj, GLU_SMOOTH);
	gluDisk(quadObj, 0.0, D, 32, 1);
	gluDeleteQuadric(quadObj);

	glPopMatrix();

}// End DrawArrow(..)

// -------------------------------------------------------------------------

// For simple displaying of lines - takes two 3D positions
// start and end of the line in the 3D world
void DrawLine(const Vector3& p0, const Vector3& p1)
{
	glPushMatrix();
	glBegin(GL_LINES);
	glColor3f(1, 0.0, 0.0); // Color RED
	glVertex3d(p0.x, p0.y, p0.z);
	glVertex3d(p1.x, p1.y, p1.z);
	glEnd();
	glPopMatrix();
}// End DrawLine(..)

// -------------------------------------------------------------------------

// Draw 3D spherical mesh in the environment
// paramaters should be self explanitory (i.e., position, radius and colour)
void DrawSphere(const Vector3& p0, float radius, float r, float g, float b)
{
	glPushMatrix();
	glColor3f(r, g, b);
	glTranslatef(p0.x, p0.y, p0.z);
	glutSolidSphere(radius, 10, 9);
	glPopMatrix();
}

// -------------------------------------------------------------------------


// Build or set of links (i.e., length and angle)
void CIkSystem::Setup()
{
	for (int i = 0; i<numLinks; ++i)
	{
		links.push_back(new Link(Vector3(0, 0, 1), (float)i*0.2f));
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
	ax = min(1, max(ax, -1));
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
	Vector3 target = GetMousePosition2Dto3D();
	DrawSphere(target, 0.16f, 0.1f, 0.5f, 0.4f);

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
		DrawSphere(GetTranslation(links[i]->m_base), 0.1f, 0.5f, 0.5f, 0.9f);

		Vector3 base = GetTranslation(links[i]->m_base);
		Vector3 end = Transform(links[i]->m_base, Vector3(linkLength, 0, 0));

		DrawArrow(base, end, 0.2f);
	}

}// End UpdateIK(..)




Vector3 GetMousePosition2Dto3D()
{
	// First get the mouse position (i.e., relative to our draw window)
	HDC hdc = ::wglGetCurrentDC();
	HWND hwnd = ::WindowFromDC(hdc);
	POINT ps;
	GetCursorPos(&ps);
	ScreenToClient(hwnd, &ps);

	// Second, project it into 3d
	float x = ps.x;
	float y = ps.y;
	GLint viewport[4];
	GLdouble modelview[16], projection[16];
	GLfloat wx = x, wy, wz;

	glGetIntegerv(GL_VIEWPORT, viewport);
	y = viewport[3] - y;
	wy = y;
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	double ox, oy, oz;

	wz = 0;
	gluUnProject(wx, wy, wz, modelview, projection, viewport, &ox, &oy, &oz);
	Vector3 v0(ox, oy, oz);

	wz = 1.0;
	gluUnProject(wx, wy, wz, modelview, projection, viewport, &ox, &oy, &oz);
	Vector3 v1(ox, oy, oz);

	// Project onto plane going through the origin
	Vector3 n(0, 0, 1);
	Vector3 p(0, 0, 0);

	float t = (Dot(p, n) - Dot(v0, n)) / Dot(n, v1 - v0);

	Vector3 p0 = v0 + (v1 - v0)*t;

	DrawSphere(p0, 0.15f, 0.2f, 0.1f, 0.3f);
	static Vector3 pre = p0;
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		pre = p0;
	}
	return pre;
}

// Graphics/Render update code
void CIkSystem::Render(void)
{
	// Camera
	glMatrixMode(GL_PROJECTION); // Use the Projection Matrix
	glLoadIdentity(); // Reset Matrix
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT); // Set the viewport to be the entire window
	gluPerspective(45.0f, (1.0f*WINDOW_WIDTH) / (1.0f*WINDOW_HEIGHT), 0.1f, 1000.0f); // Set the correct perspective.
	glMatrixMode(GL_MODELVIEW); // Get Back to the Modelview

	// Some lighting - so things look beautiful
	GLfloat amb_light[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat diffuse[] = { 0.6f, 0.6f, 0.6f, 1 };
	GLfloat specular[] = { 0.7f, 0.7f, 0.3f, 1 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb_light);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// Clear Color and Depth Buffers
	glClearColor(1.0f, 1.0f, 1.0f, 0.5f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(0.0f, 0.0f, 20.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);

	glPushMatrix();

	// Update 
	UpdateIK();

	glPopMatrix();
	glutSwapBuffers();
}
