#include "Camera.h"
#include <iostream>
#include "Utility.h"
#include "Material.h"

using namespace std;

void Camera::Render(const Hitable& rWorld){ //Anciennement dans le main

    Initialize();
    cout << "P3\n" << width << ' ' << height << "\n255\n";
    for (int y = 0; y < height; y++)
    {
        clog << "Progress : " << (y * 100 / height) << " %\n" << flush;
        for (int x = 0; x < width; x++){
            Color pixel(0, 0, 0);
            for (int sample = 0; sample < sampleCount; sample++){
                Ray ray = GetRay(x, y);
                pixel += RayColor(ray, maxBounces, rWorld);
            }

            WriteColor(cout, pixel, sampleCount);
        }
    }
    clog << "Done! You can open your file now :)\n";
}


void Camera::Initialize(){

    height = static_cast<int>(width / aspectRatio);
    if (height < 1) height = 1;

    center = camPosition;
    //double focalLength = (camPosition-target).Length();
    auto theta = DegToRad(vfov);
    auto h = tan(theta / 2);
    auto viewportHeight = 2 * h * focusDist;

    double viewportWidth = viewportHeight * (static_cast<double>(width) / height);

    w = Unit(camPosition - target);
    u = Unit(Cross(camUp, w));
    v = Cross(w, u);

    Vector3 viewportX = viewportWidth*u;
    Vector3 viewportY = -viewportHeight*v; //We invert Y

    //Delta vector between pixels
    pixelDeltaX = viewportX / width;
    pixelDeltaY = viewportY / height;

    //Position of the top left pixel
    Vector3 viewportOrigin = center - (focusDist * w) - viewportX / 2 - viewportY / 2;

    originPixelLocation = viewportOrigin + 0.5 * (pixelDeltaX + pixelDeltaY);

    // Calculate the camera defocus disk basis vectors.
    auto defocusRadius = focusDist * tan(DegToRad(defocusAngle / 2));
    DefocusDiskX = u * defocusRadius;
    DefocusDiskY = v * defocusRadius;

}


Color Camera::RayColor(const Ray& rRay, int bouncesLeft, const Hitable& rWorld) const
{
    HitInfo hitInfo;
    if (bouncesLeft <= 0) return Color(0, 0, 0);
    if (rWorld.Hit(rRay, Interval(0.001, infinity), hitInfo)) {
        Ray scattered;
        Color attenuation;
        if (hitInfo.mat->Scatter(rRay, hitInfo, attenuation, scattered))
        {
            return attenuation * RayColor(scattered, bouncesLeft - 1, rWorld);
        }
        return Color(0, 0, 0);
    }


    Vector3 unitDirection = Unit(rRay.GetDirection());
    double blue = 0.5 * (unitDirection.y + 1.0);
    return (1.0 - blue) * Color(1.0, 1.0, 1.0) + blue * Color(0.5, 0.7, 1.0);
}

Ray Camera::GetRay(int x, int y) const{

    // Get a randomly sampled camera ray for the pixel at location i,j.

    Vector3 pixelCenter = originPixelLocation + (x * pixelDeltaX) + (y * pixelDeltaY);
    Vector3 pixelSample = pixelCenter + PixelSampleSquared();

    Position rayOrigin = (defocusAngle <= 0) ? center : DefocusSample();
    Vector3 rayDirection = pixelSample - rayOrigin;

    return Ray(rayOrigin, rayDirection);
}


Vector3 Camera::PixelSampleSquared() const
{
    //Returns a random point in the square around a pixel at the origin
    double pX = -0.5 + RandomDouble();
    double pY = -0.5 + RandomDouble();
    return (pX * pixelDeltaX) + (pY * pixelDeltaY);
}

Position Camera::DefocusSample() const{
    // Returns a random point in the camera defocus disk.
    auto p = RandomDisk();
    return center + (p[0] * DefocusDiskX) + (p[1] * DefocusDiskY);
}
