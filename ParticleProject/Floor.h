#pragma once
#include "graphics/GrTexture.h"

/*
	Class representing the floor...
*/
class CFloor
{
public:
	CFloor();
	virtual ~CFloor();

	void Draw();

	// Called with the radius of the particles, so no matter their radius, it appears to bounce (would be better to do in bouncing)
	void SetHeight(double height) { mHeight = height; }
	
	void SetLength(double length) { mLength = length; }

private:
	// Floor texture
	CGrTexture mTexture;

	// Floor height
	double mHeight = 0.;

	// Floor length (box)
	double mLength = 0.;
};

