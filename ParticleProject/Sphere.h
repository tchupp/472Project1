#pragma once

#include "gl/gl.h"
#include "graphics/GrTexture.h"

class CSphere
{
public:
    CSphere(void);
    ~CSphere(void);

    void Draw();

    void SetRadius(double r) {m_radius = r;}

	double GetRadius() { return m_radius; }

	void SetTexture(CGrTexture *texture) { m_texture = texture;  }

private:
    void SphereFace(int p_recurse, double p_radius, double *a,
                            double *b, double *c);

    double m_radius;

	CGrTexture *m_texture;
};

