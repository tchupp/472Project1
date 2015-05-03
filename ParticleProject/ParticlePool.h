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

	double GetPraticleRadius() { return mParticleRadius; }
	void SetParticleRadius(double value) { mParticleRadius = value; }

	void SetParticleColor(int color) { mParticleColor = color; }

	void Update(double delta);
	void Draw();

private:
	CParticleList mActive; ///< list of active particles
	CParticleList mInactive; ///< list of inactive particles

	double mParticleRadius;
	int mParticleColor;
};

