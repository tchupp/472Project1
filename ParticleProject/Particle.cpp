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
CParticle::CParticle(Vector3 pos, Vector3 vel, double lifeTime)
{
	Spawn(pos, vel, lifeTime);
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
	mPos.Z += mVel.Z * delta;

	//update lifetime
	mLifeTime -= delta;
}

void CParticle::Spawn(Vector3 pos, Vector3 vel, double lifeTime){
	mPos = pos;
	mVel = vel;
	mLifeTime = lifeTime;
	mTotal = 0;
}

bool CParticle::Dead(){
	if (mLifeTime <= 0){
		return true;
	}
	return false;
}

/**
* \brief Draw the particle
*/
void CParticle::Draw() 
{
	glPushMatrix();
	glTranslated(mPos.X, mPos.Y, mPos.Z);
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
