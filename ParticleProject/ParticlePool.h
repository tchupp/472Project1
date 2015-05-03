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

	double GetPraticleRadius() { return mBaseRadius; }
	bool SetParticleRadius(double value);
	bool SetParticleColor(int color);
	bool SetParticleVel(double vel);
	bool SetParticleLife(double life);
	bool SetParticleVelVar(double velVar);
	bool SetParticleLifeVar(double lifeVar);
	bool SetParticleRadiusVar(double radVar);

	void Update(double delta);
	void Draw();

private:
	CParticleList mActive; ///< list of active particles
	CParticleList mInactive; ///< list of inactive particles

	Vector3 mBaseVel;
	double mBaseLifeTime;
	double mBaseRadius;
	int mParticleColor;

	double mVelVariance;
	double mLifeVariance;
	double mRadiusVariance;
};

