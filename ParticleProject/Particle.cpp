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
CParticle::CParticle(Vector3 pos, Vector3 vel) : mPos(pos), mVel(vel) {}


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
	// TODO: add gravity
	mPos.X += mVel.X * delta;
	mPos.Y += mVel.Y * delta;
	mPos.Z += mVel.Z * delta;
}


/**
* \brief Draw the particle
*/
void CParticle::Draw() {}


/**
* \brief Sets the next particle in the linked list
* \param next Next particle in the list
*/
void CParticle::SetNext(std::shared_ptr<CParticle> next)
{
	mNext = next;
	assert(mNext.get() != this);
}
