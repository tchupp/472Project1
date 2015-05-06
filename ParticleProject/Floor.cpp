#include "stdafx.h"
#include "Floor.h"


CFloor::CFloor()
{
	mTexture.LoadFile(L"textures/woodFloor.bmp");
}


CFloor::~CFloor()
{
}

//
//        Name : Quad()
// Description : Inline function for drawing 
//               a quadralateral.
//
inline void Quad(GLdouble* v1, GLdouble* v2, GLdouble* v3, GLdouble* v4)
{
	glBegin(GL_QUADS);

	glTexCoord2d(0., 0.);
	glVertex3dv(v1);

	glTexCoord2d(1., 0.);
	glVertex3dv(v2);

	glTexCoord2d(0., 1.);
	glVertex3dv(v3);

	glTexCoord2d(1., 1.);
	glVertex3dv(v4);

	glEnd();
}


void CFloor::Draw()
{
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, mTexture.TexName());

	GLdouble a[] = { 0., mHeight, 0. };
	GLdouble b[] = { 0., mHeight, 20. };
	GLdouble c[] = { 20., mHeight, 20. };
	GLdouble d[] = { 20., mHeight, 0. };

	glNormal3d(0., 0., 1.);
	Quad(a, b, c, d);

	glDisable(GL_TEXTURE_2D);
}

