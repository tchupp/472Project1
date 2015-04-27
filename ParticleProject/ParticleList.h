/**
* \file ParticleList.h
*
* \author Theo Chupp
*
* \brief linked list that keeps track of particles
*/


#pragma once
#include <memory>
#include "Particle.h"

/**
* \brief linked list that keeps track of particles
*/
class CParticleList
{
public:
	CParticleList();
	virtual ~CParticleList();

	/// returns the front of the linked list
	std::shared_ptr<CParticle> GetHead() { return mHead; }

	void PushBack(std::shared_ptr<CParticle> flake);

	bool Remove(std::shared_ptr<CParticle> flake);

	/// return the number of flakes in the list
	int GetSize() { return mSize; }

private:
	std::shared_ptr<CParticle> mHead = nullptr; ///< head pointer of the list
	std::shared_ptr<CParticle> mTail = nullptr; ///< tail pointer of the list
	int mSize; ///< number of flakes in the list
};
