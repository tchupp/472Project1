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

const int sign[2] = {-1, 1};

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
	mVelVariance = 0.2;
	mLifeVariance = 0.2;
	mRadiusVariance = 0.2;

	for (int i = 0; i < 200; i++) 
	{
		mInactive.PushBack(std::make_shared<CParticle>());
	}
}


/**
* \brief Destructor
*/
CParticlePool::~CParticlePool() {}


bool CParticlePool::SetParticleRadius(double value)
{
	double lowerBound = 0.01;

	if (value < lowerBound)
	{
		mBaseRadius = lowerBound;
		return false;
	}
	mBaseRadius = value;
	return true;
}

bool CParticlePool::SetParticleColor(int color)
{
	mParticleColor = color;
	return true;
}

bool CParticlePool::SetParticleVel(double velX, double velY, double velZ)
{
	mBaseVel.X = velX;
	mBaseVel.Y = velY;
	mBaseVel.Z = velZ;
	return true;
}

bool CParticlePool::SetParticleLife(double life)
{
	double lowerBound = 1;
	double upperBound = 10;
	if (life < lowerBound)
	{
		mBaseLifeTime = lowerBound;
		return false;
	}
	if (life > upperBound)
	{
		mBaseLifeTime = upperBound;
		return false;
	}
	mBaseLifeTime = life;
	return true;
}

bool CParticlePool::SetParticleVelVar(double velVar)
{
	double lowerBound = 0;
	double upperBound = 0.5;

	if (velVar < lowerBound)
	{
		mVelVariance = lowerBound;
		return false;
	}
	if (velVar > upperBound)
	{
		mVelVariance = upperBound;
		return false;
	}

	mVelVariance = velVar;
	return true;
}

bool CParticlePool::SetParticleLifeVar(double lifeVar)
{
	double lowerBound = 0;
	double upperBound = 0.5;

	if (lifeVar < lowerBound)
	{
		mLifeVariance = lowerBound;
		return false;
	}
	if (lifeVar > upperBound)
	{
		mLifeVariance = upperBound;
		return false;
	}

	mLifeVariance = lifeVar;
	return true;
}

bool CParticlePool::SetParticleRadiusVar(double radVar)
{
	double lowerBound = 0;
	double upperBound = 0.5;

	if (radVar < lowerBound)
	{
		mRadiusVariance = lowerBound;
		return false;
	}
	if (radVar > upperBound)
	{
		mRadiusVariance = upperBound;
		return false;
	}

	mRadiusVariance = radVar;
	return true;
}

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
	std::uniform_real_distribution<double> velVariance(0.0, mVelVariance);
	std::uniform_real_distribution<double> lifeVariance(0.0, mLifeVariance);
	std::uniform_real_distribution<double> radiusVariance(0.0, mRadiusVariance);
	while (mActive.GetSize() < MaxActive && numAdded < MaxAdded)
	{
		if (mInactive.GetSize())
		{
			vel.X = mBaseVel.X + mBaseVel.X * velVariance(re) * sign[rand() % 2];
			vel.Y = mBaseVel.Y + mBaseVel.Y * velVariance(re) * sign[rand() % 2];
			vel.Z = mBaseVel.Z + mBaseVel.Z * velVariance(re) * sign[rand() % 2];
			lifeTime = mBaseLifeTime + (mBaseLifeTime * lifeVariance(re) * sign[rand() % 2]);
			radius = mBaseRadius + mBaseRadius *  radiusVariance(re) * sign[rand() % 2];

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
