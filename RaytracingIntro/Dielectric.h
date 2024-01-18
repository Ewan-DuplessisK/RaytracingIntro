#pragma once
#include "Material.h"

class Dielectric:public Material{
public:
	Dielectric(double refract): mRefraction(refract){}

	bool Scatter(const Ray& inRay, const HitInfo& rec, Color& attenuation, Ray& scattered) const override;
	static double Reflectance(double cosine, double pRefractionIndex);

private:
	double mRefraction; // Index
};

