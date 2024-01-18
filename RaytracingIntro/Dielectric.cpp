#include "Dielectric.h"
#include "Hitable.h"

bool Dielectric::Scatter(const Ray& inRay, const HitInfo& rec, Color& attenuation, Ray& scattered) const {
	attenuation = Color(1.0, 1.0, 1.0);
	double refractRatio = rec.frontFace ? (1.0 / mRefraction) : mRefraction;
	Vector3 unitDirection = Unit(inRay.GetDirection());
	double cosTheta = fmin(Dot(-unitDirection, rec.normal), 1.0);
	double sinTheta = sqrt(1.0 - cosTheta * cosTheta);

	bool cannotRefract = refractRatio * sinTheta > 1.0;
	Vector3 direction;

	if (cannotRefract || Reflectance(cosTheta, refractRatio) > RandomDouble()) direction = Reflect(unitDirection, rec.normal);
	else direction = Refract(unitDirection, rec.normal, refractRatio);

	scattered = Ray(rec.coordinates, direction);
	return true;
}

double Dielectric::Reflectance(double cosine, double pRefractionIndex)
{
	//Shlick approximation of reflectance
	double reflectance = (1 - pRefractionIndex) / (1 + pRefractionIndex);
	reflectance *= reflectance;
	return reflectance + (1 - reflectance) * pow((1 - cosine), 5);
}

