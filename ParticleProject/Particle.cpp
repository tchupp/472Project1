/**
* \file Particle.cpp
*
* \author Theo Chupp
*/

#include "stdafx.h"
#include "Particle.h"
#include "graphics/GrTexture.h"



/**
* \brief Constructor
*/
CParticle::CParticle(Vector2 pos, Vector2 vel, Vector2 z_val) : mPos(pos), mVel(vel), mZposition_value(z_val) 
{
	mGreen.LoadFile(L"textures/green.bmp");
	mSphere.SetTexture(&mGreen);
}


/**
* \brief Destructor
*/
CParticle::~CParticle() {}


/**
* \brief updates the x and y position based on the velocity and change in time
* \param delta change in time since last update
*/
void CParticle::Update(double delta)
{
	mTotal += delta;
	mPos.X += mVel.X * delta;
	mPos.Y += (mVel.Y * delta*10.0) - mTotal;
	//mPos.Y -= (mTotal*delta);
	mZposition_value.X += mZposition_value.Y * delta;
}


/**
* \brief Draw the particle
*/
void CParticle::Draw() 
{
	glPushMatrix();
	glTranslated(mPos.X, mPos.Y, mZposition_value.X);
	mSphere.Draw();
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
