/**
* \file Particle.h
*
* \author Theo Chupp
*
* \brief Class that represents a single particle
*/

#pragma once
#include <memory>

/**
* \brief Class that represents a single particle
*/
class CParticle
{
public:
	CParticle();
	virtual ~CParticle();

	/// returns the next flake in the snowlist
	std::shared_ptr<CParticle> GetNext() { return mNext; }

	void SetNext(std::shared_ptr<CParticle> next);

private:
	std::shared_ptr<CParticle> mNext; ///< pointer to the next particle in the list
};
