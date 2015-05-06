// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "ParticleProject.h"
#include "ChildView.h"
#include "RadiusDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/// Frame duration in milliseconds
const int FrameDuration = 30;


// CChildView

CChildView::CChildView()
{
	m_camera.Set(20, 10, 50, 0, 0, 0, 0, 1, 0);
	mBoxTexture.LoadFile(L"textures/crate.bmp");
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, COpenGLWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_TIMER()
	ON_COMMAND(ID_PARTICLE_PROP, &CChildView::OnParticleProp)
END_MESSAGE_MAP()


// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!COpenGLWnd::PreCreateWindow(cs)) return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
	                                             ::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), NULL);

	

	return TRUE;
}




void CChildView::OnGLDraw(CDC* pDC)
{
	if (mFirstDraw)
	{
		mFirstDraw = false;
		SetTimer(1, FrameDuration, nullptr);

		/*
		* Initialize the elapsed time system
		*/
		LARGE_INTEGER time, freq;
		QueryPerformanceCounter(&time);
		QueryPerformanceFrequency(&freq);

		mLastTime = time.QuadPart;
		mTimeFreq = double(freq.QuadPart);
	}
	/*
	* Compute the elapsed time since the last draw
	*/
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	long long diff = time.QuadPart - mLastTime;
	double elapsed = double(diff) / mTimeFreq;
	mParticlePool.Update(elapsed);
	mLastTime = time.QuadPart;

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
	GLfloat lightpos[] = {0.5, 2.0, 1.0, 0.};
	glPushMatrix();
	glTranslated(0.5, 2.0, 1.0);
	glRotated(45.0, 1, 0, 1);
	glTranslated(-0.5, -2.0, -1.0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	glPopMatrix();

//	GLfloat secondLightPos[] = { 0., 2.0, 2.0, 0. };
//	glPushMatrix();
//	glTranslated(0., 2.0, 2.0);
//	glRotated(45.0, 1, 0, 1);
//	glTranslated(0., -2.0, -2.0);
//	glLightfv(GL_LIGHT0, GL_POSITION, secondLightPos);
//	glPopMatrix();

	// Drawing our box (the object)
	const double RED[] = { 0.7, 0.0, 0.0 };
	glPushMatrix();
	glTranslated(3, 0, 3);
	Box(3., 3., 3., RED);
	glPopMatrix();

	// Drawing the floor
	glPushMatrix();
	mFloor.SetHeight(-1 * mParticlePool.GetParticleRadius());
	mFloor.SetLength(50.);
	mFloor.Draw();
	glPopMatrix();

	//Drawing the particles
	mParticlePool.Draw();

	// Disable lighting
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);

	// Draw a coordinate axis
//	glColor3d(0., 1., 1.);
//
//	glBegin(GL_LINES);
//	glVertex3d(0., 0., 0.);
//	glVertex3d(12., 0., 0.);
//	glVertex3d(0., 0., 0.);
//	glVertex3d(0., 12., 0.);
//	glVertex3d(0., 0., 0.);
//	glVertex3d(0., 0., 12.);
//	glEnd();
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
	GLdouble shift[] = { -3., 0., -3. };

	GLdouble a[] = { 0. + shift[0], 0. + shift[1], p_z + shift[2] };
	GLdouble b[] = { p_x + shift[0], 0. + shift[1], p_z + shift[2] };
	GLdouble c[] = { p_x + shift[0], p_y + shift[1], p_z + shift[2] };
	GLdouble d[] = { 0. + shift[0], p_y + shift[1], p_z + shift[2] };
	GLdouble e[] = { 0. + shift[0], 0. + shift[1], 0. + shift[2] };
	GLdouble f[] = { p_x + shift[0], 0. + shift[1], 0. + shift[2] };
	GLdouble g[] = { p_x + shift[0], p_y + shift[1], 0. + shift[2] };
	GLdouble h[] = { 0. + shift[0], p_y + shift[1], 0. + shift[2] };

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, mBoxTexture.TexName());

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

	glDisable(GL_TEXTURE_2D);
}

void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_camera.MouseDown(point.x, point.y);

	COpenGLWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_camera.MouseMove(point.x, point.y, nFlags)) Invalidate();

	COpenGLWnd::OnMouseMove(nFlags, point);
}


void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	m_camera.MouseDown(point.x, point.y, 2);

	COpenGLWnd::OnRButtonDown(nFlags, point);
}


void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	Invalidate();
	COpenGLWnd::OnTimer(nIDEvent);
}


void CChildView::OnParticleProp()
{
	CRadiusDlg dlg;

	dlg.mColor = mParticlePool.GetParticleColor();
	dlg.mBaseVelocityX = mParticlePool.GetParticleVelX();
	dlg.mBaseVelocityY = mParticlePool.GetParticleVelY();
	dlg.mBaseVelocityZ = mParticlePool.GetParticleVelZ();
	dlg.mBaseLife = mParticlePool.GetParticleLife();
	dlg.mVelVar = mParticlePool.GetParticleVelVar();
	dlg.mLifeVar = mParticlePool.GetParticleLifeVar();
	dlg.mRadVar = mParticlePool.GetParticleRadiusVar();
	dlg.mBaseRadius = mParticlePool.GetParticleRadius();

	dlg.mMotionBlur = GetMotionBlur();

	if (dlg.DoModal() == IDOK)
	{
		mParticlePool.SetParticleColor(dlg.mColor);
		mParticlePool.SetParticleVel(dlg.mBaseVelocityX,
			                         dlg.mBaseVelocityY,
			                         dlg.mBaseVelocityZ);

		mParticlePool.SetParticleLife(dlg.mBaseLife);
		mParticlePool.SetParticleVelVar(dlg.mVelVar);
		mParticlePool.SetParticleLifeVar(dlg.mLifeVar);
		mParticlePool.SetParticleRadiusVar(dlg.mRadVar);
		mParticlePool.SetParticleRadius(dlg.mBaseRadius);

		SetMotionBlur(dlg.mMotionBlur);
	}
}

/*
	Draws a quad, and tiles appropriately (default 1)
*/
void CChildView::Quad(GLdouble* v1, GLdouble* v2, GLdouble* v3, GLdouble* v4, int tiles)
{
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3dv(v1);
	glTexCoord2f(tiles, 0);
	glVertex3dv(v2);
	glTexCoord2f(tiles, tiles);
	glVertex3dv(v3);
	glTexCoord2f(0, tiles);
	glVertex3dv(v4);
	glEnd();
}