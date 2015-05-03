/**
* \file Particle.cpp
*
* \author Theo Chupp
*/

#include "stdafx.h"
#include "Particle.h"
#include "graphics/GrTexture.h"
#include <random>
#include "math.h"


std::default_random_engine generator;
std::uniform_int_distribution<int> distribution(0, 5);


/**
* \brief Constructor
*/
CParticle::CParticle(Vector3 pos, Vector3 vel, double lifeTime, double radius)
{
	Spawn(pos, vel, lifeTime, radius);
	mGreen.LoadFile(L"textures/green.bmp");
	mRed.LoadFile(L"textures/red.bmp");
	mBlue.LoadFile(L"textures/blue.bmp");
	mPink.LoadFile(L"textures/pink.bmp");
	mYellow.LoadFile(L"textures/yellow.bmp");

	SetColor(-1);
}



/**
* \brief Destructor
*/
CParticle::~CParticle() {}

CParticle::CParticle() : CParticle(Vector3(0.0, 0.0, 0.0), Vector3(0.0, 0.0, 0.0), 0.0, 0.3) {}

/**
* \brief updates the x and y position based on the velocity and change in time
* \param delta change in time since last update
*/
void CParticle::Update(double delta)
{
	// update velocity
	mVel.X += mAcc.X * delta;
	mVel.Y += mAcc.Y * delta;
	mVel.Z += mAcc.Z * delta;

	// update position
	mPos.X += mVel.X * delta;
	mPos.Y += mVel.Y * delta;
	mPos.Z += mVel.Z * delta;

	// bounce
	if (mPos.Y < 0 && mVel.Y < 0)
	{
		mVel.Y = abs(mVel.Y / 1.2);
	}

	//update lifetime
	mLifeTime -= delta;
}

void CParticle::Spawn(Vector3 pos, Vector3 vel, double lifeTime, double radius)
{
	mPos = pos;
	mVel = vel;
	mAcc = Vector3(0.0, -20.0, 0.0);
	mLifeTime = lifeTime;
	SetRadius(radius);
}

bool CParticle::Dead(){
	if (mLifeTime <= 0){
		return true;
	}
	return false;
}

/**
* \brief Draw the particle
*/
void CParticle::Draw() 
{
	glPushMatrix();
	glTranslated(mPos.X, mPos.Y, mPos.Z);
	mSphere.Draw();
	glPopMatrix();
}




/**
* \brief Sets the next particle in the linked list
* \param next Next particle in the list
*/
void CParticle::SetNext(std::shared_ptr<CParticle> next)
{
	mNext = next;
	assert(mNext.get() != this);
}


void CParticle::SetColor(int value)
{
	int color = value;
	CGrTexture textureColor;

	if (color == -1)
	{
		double x = rand() / static_cast<double>(RAND_MAX + 1.0);

		color = 1 + static_cast<int>(x * (5));
	}

	switch (color)
	{
	case 1:
	{
		mSphere.SetTexture(&mGreen);
		break;
	}
	case 2:
	{
		mSphere.SetTexture(&mRed);
		break;
	}
	case 3:
	{
		mSphere.SetTexture(&mBlue);
		break;
	}
	case 4:
	{
		mSphere.SetTexture(&mYellow);
		break;
	}
	case 5:
	{
		mSphere.SetTexture(&mPink);
		break;
	}
	default:
	{
		mSphere.SetTexture(&mGreen);
		break;
	}
	}
}