/**
* \file Particle.h
*
* \author Theo Chupp
*
* \brief Class that represents a single particle
*/

#pragma once
#include <memory>
#include "graphics/OpenGLWnd.h"
#include "graphics/GrCamera.h"
#include "graphics/GrTexture.h"
#include "Sphere.h"


/**
* \brief Class that represents a single particle
*/
class CParticle : public COpenGLWnd
{
public:
	CParticle(Vector3 pos, Vector3 vel, double lifeTime);
	virtual ~CParticle();

	/** \brief Default constructor disabled */
	CParticle();
	/** \brief Copy constructor disabled */
	CParticle(const CParticle &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CParticle &) = delete;
	void Spawn(Vector3 pos, Vector3 vel, double lifeTime);
	bool Dead();
	void SetRadius(double value) { mSphere.SetRadius(value); }
	void Update(double delta);
	void Draw();

	Vector3 GetPosition() { return mPos; }

	/// returns the next flake in the snowlist
	std::shared_ptr<CParticle> GetNext() { return mNext; }
	void SetNext(std::shared_ptr<CParticle> next);

private:
	Vector3 mPos;
	Vector3 mVel;
	Vector3 mAcc;
	double mLifeTime;

	CSphere mSphere;
	CGrTexture mGreen;
	CGrTexture mRed;
	CGrTexture mBlue;
	CGrTexture mYellow;
	CGrTexture mPink;

	std::shared_ptr<CParticle> mNext; ///< pointer to the next particle in the list
};
