#pragma once
#include "Material.h"

class MetalMaterial :public Material{

private:
	Color mAlbedo;

public:
	MetalMaterial(const Color& baseColor) : mAlbedo(baseColor) {}

	bool Scatter(const Ray& rRayIn, const HitInfo& hitInfo, Color& attenuation, Ray& scattered) const override;
};
