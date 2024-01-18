#pragma once
#include "Material.h"

class MetalMaterial :public Material{

private:
	Color mAlbedo;
	double mFuzz;

public:
	MetalMaterial(const Color& baseColor, double f) : mAlbedo(baseColor), mFuzz(f < 1 ? f : 1) {}

	bool Scatter(const Ray& rRayIn, const HitInfo& hitInfo, Color& attenuation, Ray& scattered) const override;
};
