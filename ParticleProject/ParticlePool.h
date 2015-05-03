/**
* \file ParticlePool.h
*
* \author Theo Chupp
*
* \brief Controller class for the snowfall
*/

#pragma once
#include "ParticleList.h"


class CParticlePool
{
public:
	CParticlePool();
	virtual ~CParticlePool();

	/** \brief Copy constructor disabled */
	CParticlePool(const CParticlePool&) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CParticlePool&) = delete;

	void Update(double delta);
	void Draw();

private:
	CParticleList mActive; ///< list of active particles
	CParticleList mInactive; ///< list of inactive particles

	Vector3 mBaseVel;
	double mBaseLifeTime;
};

