#pragma once
#include "Hitable.h"

class Sphere : public Hitable
{
private:
	Position mCenter;
	double mRadius;
public:
	Sphere(Position center, double radius) :mCenter(center), mRadius(radius) {}
	bool Hit(const Ray& rRay, Interval rayTime, HitInfo& hitInfo) const override;

};
