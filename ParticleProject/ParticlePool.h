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

	double GetParticleRadius() { return mBaseRadius; }
	bool SetParticleRadius(double value);

	int GetParticleColor() { return mParticleColor; }
	bool SetParticleColor(int color);

	double GetParticleVelX() { return mBaseVel.X; }
	double GetParticleVelY() { return mBaseVel.Y; }
	double GetParticleVelZ() { return mBaseVel.Z; }
	bool SetParticleVel(double velX, double velY, double velZ);

	double GetParticleLife() { return mBaseLifeTime; }
	bool SetParticleLife(double life);

	double GetParticleVelVar() { return mVelVariance; }
	bool SetParticleVelVar(double velVar);

	double GetParticleLifeVar() { return mLifeVariance; }
	bool SetParticleLifeVar(double lifeVar);

	double GetParticleRadiusVar() { return mRadiusVariance; }
	bool SetParticleRadiusVar(double radVar);

	int GetMaxActive() { return MaxActive; }
	bool SetMaxActive(int maxActive);

	void Update(double delta);
	void Draw();

private:
	int MaxActive;
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

