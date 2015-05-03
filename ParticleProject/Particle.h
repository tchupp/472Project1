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
	CParticle(Vector2 pos, Vector2 vel, Vector2 zVal);
	virtual ~CParticle();

	/** \brief Default constructor disabled */
	CParticle() = delete;
	/** \brief Copy constructor disabled */
	CParticle(const CParticle &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CParticle &) = delete;

	void Update(double delta);
	void Draw();

	Vector2 GetPosition() { return mPos; }

	/// returns the next flake in the snowlist
	std::shared_ptr<CParticle> GetNext() { return mNext; }
	void SetNext(std::shared_ptr<CParticle> next);

private:
	Vector2 mPos;
	Vector2 mVel;
	Vector2 mZposition_value;
	double mTotal=0;

	CSphere mSphere;
	CGrTexture mGreen;

	std::shared_ptr<CParticle> mNext; ///< pointer to the next particle in the list
};
