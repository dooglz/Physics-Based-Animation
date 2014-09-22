
#include "windows.h"
#include "GL/glut.h"
#include "utilities.h"

#include "helpermath.h" // Vector3, Matrix4, and Quaternion
#include "renderer.h"
#include <math.h>

#define RADPERDEG 0.0174533
// Basic Draw Functions (e.g., for lines, points )

// Takes three paramaters, i.e., the start and end position in 3D
// of the arrow position in the world, and the size of the arrow

void CRenderer::DrawArrow(const Vector3& p0, const Vector3& p1, double D)
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
void CRenderer::DrawLine(const Vector3& p0, const Vector3& p1)
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
void CRenderer::DrawSphere(const Vector3& p0, float radius, float r, float g, float b)
{
	glPushMatrix();
	glColor3f(r, g, b);
	glTranslatef(p0.x, p0.y, p0.z);
	glutSolidSphere(radius, 10, 9);
	glPopMatrix();
}

// -------------------------------------------------------------------------

void CRenderer::PrepForRender(){
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
	gluLookAt(	0.0f, 0.0f, 30.0f,
				0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f);

	glPushMatrix();
}

Vector3 CRenderer::GetMousePosition2Dto3D()
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

	return v0 + (v1 - v0)*t;
}

void CRenderer::FinishRender(){
	glPopMatrix();
	glutSwapBuffers();
}
