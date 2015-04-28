/**
* \file ParticlePool.cpp
*
* \author Theo Chupp
*/

#include "stdafx.h"
#include "ParticlePool.h"

/// max number of particles allowed to be added per update
const int MaxAdded = 5; ///< will actually be total particles over time of animation

/// total number of active snowflakes
const int MaxActive = 400;

/**
* \brief Constructor
*/
CParticlePool::CParticlePool() {}


/**
* \brief Destructor
*/
CParticlePool::~CParticlePool() {}


/**
* \brief updates the active and inactive pools
*		 adds new particles to active if needed
*        updates the position on the screen
* \param delta
*/
void CParticlePool::Update(double delta)
{
	// determine if any particles require removing
	for (auto particle = mActive.GetHead(); particle != nullptr; particle = particle->GetNext())
	{
		// if particle requires removing
			//mActive.Remove(particle);
			//mInactive.PushBack(particle);
	}

	// add more particles if needed
	auto numAdded = 0;
	while (mActive.GetSize() < MaxActive && numAdded < MaxAdded)
	{
		if (mInactive.GetSize())
		{
			auto particle = mInactive.GetHead();
			mInactive.Remove(particle);
			//particle->ResetPosition();
			mActive.PushBack(particle);
		}
		numAdded++;
	} // I might just want to add a certain number each update, like delta / total time - Theo

	// update position of all the active particles
	for (auto particle = mActive.GetHead(); particle != nullptr; particle = particle->GetNext())
	{
		particle->Update(delta);
	}
}


/**
* \brief Draw all the particles in the active pool
*/
void CParticlePool::Draw()
{
	for (auto particle = mActive.GetHead(); particle != nullptr; particle = particle->GetNext())
	{
		particle->Draw();
	}
}
