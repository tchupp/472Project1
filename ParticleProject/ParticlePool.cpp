/**
* \file ParticlePool.cpp
*
* \author Theo Chupp
*/

#include "stdafx.h"
#include "ParticlePool.h"
#include "Particle.h"
#include <random>

/// max number of particles allowed to be added per update
const int MaxAdded = 7; ///< will actually be total particles over time of animation

/// total number of active snowflakes
const int MaxActive = 100;

int sign[2] = {-1, 1};
std::uniform_real_distribution<double> variance(0.0, 0.3);
std::default_random_engine re;

/**
* \brief Constructor
*/
CParticlePool::CParticlePool() 
{
	mBaseVel = Vector3(5.0, 20.0, 5.0);
	mBaseLifeTime = 5.0;
	mBaseRadius = 0.3;
	mParticleColor = -1;

	for (int i = 0; i < 100; i++) 
	{
		mInactive.PushBack(std::make_shared<CParticle>());
	}
}


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
		if (particle->Dead())
		{
			mActive.Remove(particle);
			mInactive.PushBack(particle);
		}		
	}

	// add more particles if needed
	auto numAdded = 0;
	Vector3 vel;
	double lifeTime;
	double radius;
	while (mActive.GetSize() < MaxActive && numAdded < MaxAdded)
	{
		if (mInactive.GetSize())
		{
			vel.X = mBaseVel.X + mBaseVel.X * variance(re) * sign[rand() % 2];
			vel.Y = mBaseVel.Y + mBaseVel.Y * variance(re) * sign[rand() % 2];
			vel.Z = mBaseVel.Z + mBaseVel.Z * variance(re) * sign[rand() % 2];
			lifeTime = mBaseLifeTime + (mBaseLifeTime * variance(re) * sign[rand() % 2]);
			radius = mBaseRadius + mBaseRadius *  variance(re) * sign[rand() % 2];

			auto particle = mInactive.GetHead();
			mInactive.Remove(particle);
			particle->SetColor(mParticleColor);
			particle->Spawn(Vector3(0, 0, 0), vel, lifeTime, radius);

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
