#include "Material.h"
#include "Hitable.h"

bool Lambertian::Scatter(const Ray& inRay, const HitInfo& rec, Color& attenuation, Ray& scattered) const {

    auto scatterDirection = rec.normal + RandomUnitVector();
    scattered = Ray(rec.coordinates, scatterDirection);
    attenuation = mAlbedo;
    return true;
}