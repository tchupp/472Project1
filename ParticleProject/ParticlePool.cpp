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
const int MaxActive = 100000;

std::uniform_real_distribution<double> unif(-5.0, 5.0);
std::uniform_real_distribution<double> unif1(1.0, 3.0);
std::uniform_real_distribution<double> unif2(-5.0, 5.0);
std::uniform_real_distribution<double> rand_lifetime(1.0, 3.0);
std::default_random_engine re;

/**
* \brief Constructor
*/
CParticlePool::CParticlePool() {
	for (int i = 0; i < 10; i++) {
		double a_random_double = unif(re);
		double a_random_double2 = unif(re);
		double a_random_double3 = unif(re);
		double life_time = rand_lifetime(re);
		mActive.PushBack(std::make_shared<CParticle>(Vector3(0, 0, 0), Vector3(a_random_double, a_random_double2, a_random_double3), life_time));
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
	while (mActive.GetSize() < MaxActive && numAdded < MaxAdded)
	{
		if (mInactive.GetSize())
		{
			double a_random_double = unif(re);
			double a_random_double2 = unif1(re);
			double a_random_double3 = unif2(re);
			double life_time = rand_lifetime(re);

			auto particle = mInactive.GetHead();
			mInactive.Remove(particle);
			particle->Spawn(Vector3(0, 0, 0), Vector3(a_random_double, a_random_double2, a_random_double3), life_time);
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
