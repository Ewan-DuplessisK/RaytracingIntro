#pragma once
#include "Ray.h"
#include "Interval.h"

class Material;

class HitInfo
{
public:
    Position coordinates;
    Vector3 normal;
    double time;
    bool frontFace;
    shared_ptr<Material> mat;

    void SetFaceNormal(const Ray& rRay, const Vector3& outwardNormal)
    {
        //NOTE : The outwardNormal vector should be unit length
        frontFace = Dot(rRay.GetDirection(), outwardNormal) < 0;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};


class Hitable
{
public:
	virtual ~Hitable() = default;
    virtual bool Hit(const Ray& rRay, Interval rayTime, HitInfo& hitInfo) const = 0;
};
