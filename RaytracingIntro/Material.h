#pragma once

#include "Color.h"
#include "Ray.h"

class HitInfo;

class Material
{
public:
	~Material() = default;

	virtual bool Scatter(const Ray& rayIn, const HitInfo& hitInfo, Color& attenuation, Ray& scattered) const = 0;
};

class Lambertian : public Material {
public:
    Lambertian(const Color& albedo) : mAlbedo(albedo) {}

    bool Scatter(const Ray& inRay, const HitInfo& rec, Color& attenuation, Ray& scattered) const override;

private:
    Color mAlbedo;
};