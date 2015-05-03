// ChildView.h : interface of the CChildView class
//


#pragma once

#include "graphics/OpenGLWnd.h"
#include "graphics/GrCamera.h"
#include "ParticlePool.h"

// CChildView window

class CChildView : public COpenGLWnd
{
public:
	CChildView();
	virtual ~CChildView();
	void OnGLDraw(CDC* pDC) override;
	void Box(GLdouble p_x, GLdouble p_y, GLdouble p_z, const GLdouble* p_color);

protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs) override;

private:
	// Attributes

private:
	CGrCamera m_camera;
	CParticlePool mParticle;

	/// True until the first time we draw
	bool mFirstDraw = true;

	long long mLastTime;    ///< Last time we read the timer
	double mTimeFreq;       ///< Rate the timer updates

	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnParticleRadius();
};
