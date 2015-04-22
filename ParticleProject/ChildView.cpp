// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "ParticleProject.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	m_camera.Set(20, 10, 50, 0, 0, 0, 0, 1, 0);
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, COpenGLWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()


// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!COpenGLWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
	                                             ::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), NULL);

	return TRUE;
}


void CChildView::OnGLDraw(CDC* pDC)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//
	// Set up the camera
	//
	int width, height;
	GetSize(width, height);
	m_camera.Apply(width, height);

	//
	// Some standard parameters
	//

	// Enable depth test
	glEnable(GL_DEPTH_TEST);

	// Cull backfacing polygons
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	
	// Enable lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// light position
	GLfloat lightpos[] = { 0.5, 2.0, 1.0, 0. };
	glPushMatrix();
	glTranslated(0.5, 2.0, 1.0);
	glRotated(45.0, 1, 0, 1);
	glTranslated(-0.5, -2.0, -1.0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	glPopMatrix();

	// Draw cube
	const double RED[] = { 0.7, 0.0, 0.0 };
	glPushMatrix();
	glTranslated(1.5, 1.5, 1.5);
	glRotated(45.0, 45.0, 45.0, 1.);
	glTranslated(-1.5, -1.5, -1.5);
	Box(3., 3., 3., RED);
	glPopMatrix();

	// Disable lighting
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);

	// Draw a coordinate axis
	glColor3d(0., 1., 1.);

	glBegin(GL_LINES);
	glVertex3d(0., 0., 0.);
	glVertex3d(12., 0., 0.);
	glVertex3d(0., 0., 0.);
	glVertex3d(0., 12., 0.);
	glVertex3d(0., 0., 0.);
	glVertex3d(0., 0., 12.);
	glEnd();
}

//
//        Name : Quad()
// Description : Inline function for drawing 
//               a quadralateral.
//
inline void Quad(GLdouble* v1, GLdouble* v2, GLdouble* v3, GLdouble* v4)
{
	glBegin(GL_QUADS);
	glVertex3dv(v1);
	glVertex3dv(v2);
	glVertex3dv(v3);
	glVertex3dv(v4);
	glEnd();
}

//
//        Name : CChildView::Box()
// Description : Draw an arbitrary size box. p_x, 
//               p_y, an p_z are the height of
//               the box. We will use this 
//               as a common primitive.
//      Origin : The back corner is at 0, 0, 0, and
//               the box is entirely in the
//               positive octant.
//
void CChildView::Box(GLdouble p_x, GLdouble p_y, GLdouble p_z, const GLdouble* p_color)
{
	GLdouble a[] = { 0., 0., p_z };
	GLdouble b[] = { p_x, 0., p_z };
	GLdouble c[] = { p_x, p_y, p_z };
	GLdouble d[] = { 0., p_y, p_z };
	GLdouble e[] = { 0., 0., 0. };
	GLdouble f[] = { p_x, 0., 0. };
	GLdouble g[] = { p_x, p_y, 0. };
	GLdouble h[] = { 0., p_y, 0. };

	glNormal3d(0., 0., 1.);
	Quad(a, b, c, d); // Front

	glNormal3d(1., 0., 0.);
	Quad(c, b, f, g); // Right

	glNormal3d(0., 0., -1.);
	Quad(h, g, f, e); // Back

	glNormal3d(-1., 0., 0.);
	Quad(d, h, e, a); // Left

	glNormal3d(0., 1., 0.);
	Quad(d, c, g, h); // Top

	glNormal3d(0., -1., 0.);
	Quad(e, f, b, a); // Bottom
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_camera.MouseDown(point.x, point.y);

	COpenGLWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_camera.MouseMove(point.x, point.y, nFlags))
		Invalidate();

	COpenGLWnd::OnMouseMove(nFlags, point);
}


void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	m_camera.MouseDown(point.x, point.y, 2);

	COpenGLWnd::OnRButtonDown(nFlags, point);
}
