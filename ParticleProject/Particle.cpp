/**
* \file Particle.cpp
*
* \author Theo Chupp
*/

#include "stdafx.h"
#include "Particle.h"



/**
* \brief Constructor
*/
CParticle::CParticle(Vector3 pos, Vector3 vel, double lifeTime)
{
	Spawn(pos, vel, lifeTime);
}


/**
* \brief Destructor
*/
CParticle::~CParticle() {}


bool CParticle::Dead()
{
	if (mLifeTime <= 0)
	{
		return true;
	}
	return false;
}

void CParticle::Spawn(Vector3 pos, Vector3 vel, double lifeTime)
{
	mPos = pos;
	mVel = vel;
	mLifeTime = lifeTime;
	mTotal = 0;
}

/**
* \brief updates the x and y position based on the velocity and change in time
* \param delta change in time since last update
*/
void CParticle::Update(double delta)
{
	mTotal += delta;

	// update position
	mPos.X += mVel.X * delta;
	mPos.Y += (mVel.Y * delta*10.0) - mTotal;
	//mPos.Y -= (mTotal*delta);
	mPos.Z += mVel.Z * delta;

	// update lifetime
	mLifeTime -= delta;
}


/**
* \brief Draw the particle
*/
void CParticle::Draw() 
{

	
	// Draw cube
	const double RED[] = {0.7, 0.0, 0.0};
	glPushMatrix();
	glTranslated(mPos.X, mPos.Y, mPos.Z);
	//glRotated(45.0, 45.0, 45.0, 1.);
	//glTranslated(-mPos.X, -mPos.Y, -1.5);
	GLdouble p_x = 1.;
	GLdouble p_y = 1.;
	GLdouble p_z = 1.;

	GLdouble a[] = { 0., 0., p_z };
	GLdouble b[] = { p_x, 0., p_z };
	GLdouble c[] = { p_x, p_y, p_z };
	GLdouble d[] = { 0., p_y, p_z };
	GLdouble e[] = { 0., 0., 0. };
	GLdouble f[] = { p_x, 0., 0. };
	GLdouble g[] = { p_x, p_y, 0. };
	GLdouble h[] = { 0., p_y, 0. };

	glNormal3d(0., 0., 1.);
	glBegin(GL_QUADS);
	glVertex3dv(a);
	glVertex3dv(b);
	glVertex3dv(c);
	glVertex3dv(d);
	glEnd();

	glNormal3d(1., 0., 0.);
	glBegin(GL_QUADS);
	glVertex3dv(c);
	glVertex3dv(b);
	glVertex3dv(f);
	glVertex3dv(g);
	glEnd();

	glNormal3d(0., 0., -1.);
	glBegin(GL_QUADS);
	glVertex3dv(h);
	glVertex3dv(g);
	glVertex3dv(f);
	glVertex3dv(e);
	glEnd();

	glNormal3d(-1., 0., 0.);
	glBegin(GL_QUADS);
	glVertex3dv(d);
	glVertex3dv(h);
	glVertex3dv(e);
	glVertex3dv(a);
	glEnd();

	glNormal3d(0., 1., 0.);
	glBegin(GL_QUADS);
	glVertex3dv(d);
	glVertex3dv(c);
	glVertex3dv(g);
	glVertex3dv(h);
	glEnd();

	glNormal3d(0., -1., 0.);
	glBegin(GL_QUADS);
	glVertex3dv(e);
	glVertex3dv(f);
	glVertex3dv(b);
	glVertex3dv(a);
	glEnd();



	glPopMatrix();



}




/**
* \brief Sets the next particle in the linked list
* \param next Next particle in the list
*/
void CParticle::SetNext(std::shared_ptr<CParticle> next)
{
	mNext = next;
	assert(mNext.get() != this);
}
