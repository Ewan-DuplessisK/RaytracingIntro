#pragma once
#include "Material.h"

class LambertianMaterial:public Material{

private:
	Color mAlbedo;

public:
	LambertianMaterial(const Color& baseColor):mAlbedo(baseColor){}

	bool Scatter(const Ray& inRay, const HitInfo& hitInfo, Color& attenuation, Ray& scattered) const override;
};

