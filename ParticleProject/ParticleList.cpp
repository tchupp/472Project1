/**
* \file ParticleList.cpp
*
* \author Theo Chupp
*/

#include "stdafx.h"
#include "ParticleList.h"


/**
* \brief Constructor
*/
CParticleList::CParticleList() : mSize(0) {}


/**
* \brief Destructor
*/
CParticleList::~CParticleList() {}


/**
* \brief Add the snowflake to the end of the list
* \param flake Flake to add to the list
*/
void CParticleList::PushBack(std::shared_ptr<CParticle> particle)
{
	assert(particle != nullptr);
	mSize++;
	if (mHead == nullptr)
	{
		mHead = particle;
		mTail = particle;
	}
	else
	{
		mTail->SetNext(particle);
		mTail = particle;
	}
}


/**
* \brief Remove the exact flake
* \param flake SnowFlake to remove
* \returns If the remove was successful
*/
bool CParticleList::Remove(std::shared_ptr<CParticle> particle)
{
	if (mHead == particle)
	{
		if (mHead != mTail)
		{
			auto temp = mHead->GetNext();
			mHead->SetNext(nullptr);
			mHead = temp;
		}
		else
		{
			mHead = nullptr;
			mTail = nullptr;
		}
		mSize--;
		return true;
	}

	for (auto node = mHead; node != mTail; node = node->GetNext())
	{
		if (node->GetNext() == particle)
		{
			auto temp = node->GetNext();
			node->SetNext(temp->GetNext());
			if (temp == mTail)
			{
				mTail = node;
			}
			mSize--;

			temp->SetNext(nullptr);

			return true;
		}
	}
	return false;
}
