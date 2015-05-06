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
//			* The number of tiles will be = tiles * tiles
//
inline void Quad(GLdouble* v1, GLdouble* v2, GLdouble* v3, GLdouble* v4, int tiles=1)
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


void CFloor::Draw()
{
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, mTexture.TexName());

	GLdouble a[] = { 0., mHeight, 0. };
	GLdouble b[] = { 0., mHeight, mLength };
	GLdouble c[] = { mLength, mHeight, mLength };
	GLdouble d[] = { mLength, mHeight, 0. };

	glNormal3d(0., 0., 1.);
	Quad(a, b, c, d, (int)(mLength / 10));

	glDisable(GL_TEXTURE_2D);
}

