#include "LambertianMaterial.h"
#include "Hitable.h"

bool LambertianMaterial::Scatter(const Ray& rayIn, const HitInfo& hitInfo, Color& attenuation, Ray& scattered) const
{
	Vector3 scatterDirection = hitInfo.normal + RandomUnitVector();

	//Catch invalid directions
	if (scatterDirection.NearZero()) scatterDirection = hitInfo.normal;

	scattered = Ray(hitInfo.coordinates, scatterDirection);
	attenuation = mAlbedo;
	return true;
}

