// ChildView.h : interface of the CChildView class
//


#pragma once

#include "graphics/OpenGLWnd.h"
#include "graphics/GrCamera.h"

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

	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};
