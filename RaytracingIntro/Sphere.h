#pragma once
#include "Hitable.h"

class Sphere : public Hitable
{
private:
	Position mCenter;
	double mRadius;
	shared_ptr<Material> mMaterial;
public:
	Sphere(Position center, double radius, shared_ptr<Material> mat) :mCenter(center), mRadius(radius), mMaterial(mat) {}
	bool Hit(const Ray& rRay, Interval rayTime, HitInfo& hitInfo) const override;

};
