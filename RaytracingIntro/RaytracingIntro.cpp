// RaytracingIntro.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Color.h"
#include "Ray.h"
#include "Utility.h"
#include "HitableCollection.h"
#include "Sphere.h"

using namespace std;

/*double HitSphere(const Position& rCenter, double radius, const Ray& rRay)
{
    Vector3 oC = rRay.GetOrigin() - rCenter;
    double a = rRay.GetDirection().SquaredLength();
    double halfB = Dot(oC, rRay.GetDirection());
    double c = oC.SquaredLength() - radius * radius;

    double discriminant = halfB * halfB - a * c;

    if (discriminant < 0) return -1.0;

    return (-halfB - sqrt(discriminant)) / a;
}*/


Color RayColor(const Ray& rRay, const Hitable& rWorld)
{
    HitInfo hitInfo;
    if (rWorld.Hit(rRay, Interval(0, infinity), hitInfo)) {
        return 0.5 * (hitInfo.normal + Color(1, 1, 1));
    }
    Vector3 unitDirection = Unit(rRay.GetDirection());
    double blue = 0.5 * (unitDirection.y + 1.0);
    return (1.0 - blue) * Color(1.0, 1.0, 1.0) + blue * Color(0.5, 0.7, 1.0);
}


int main(int argc, char* argv[])
{
    //Resolution
    double resolution = 16.0 / 9.0;
    int width = 400, height = static_cast<int>(width / resolution);
    if (height < 1) height = 1;

    //Viewport
    double viewportHeight = 2;
    double viewportWidth = viewportHeight * (static_cast<double>(width) / height);
    double focalLength = 1;
    Position cameraCenter = Position(0, 0, 0);

    Vector3 viewportX = Vector3(viewportWidth, 0, 0);
    Vector3 viewportY = Vector3(0, -viewportHeight, 0); //We invert Y

    //Delta vector between pixels
    Vector3 pixelDeltaX = viewportX / width;
    Vector3 pixelDeltaY = viewportY / height;

    //Position of the top left pixel
    Vector3 viewportOrigin = cameraCenter - Vector3(0, 0, focalLength)
        - viewportX / 2 - viewportY / 2;

    Vector3 originPixelLocation = viewportOrigin + 0.5 * (pixelDeltaX + pixelDeltaY);

    //World
    HitableCollection world;
    world.Add(make_shared<Sphere>(Position(0, 0, -1), 0.5));
    world.Add(make_shared<Sphere>(Position(0, -100.5, 0), 100));

    //Image definition
    cout << "P3\n" << width << ' ' << height << "\n255\n"; //Header
    for (int y = 0; y < height; y++) {
        clog << "Progress : " << (y * 100 / height) << " %\n" << flush;

        for (int x = 0; x < width; x++) {
            Vector3 pixelCenter = originPixelLocation + (x * pixelDeltaX) + (y * pixelDeltaY);
            Vector3 rayDirection = pixelCenter - cameraCenter;
            Ray ray(cameraCenter, rayDirection);

            Color pixel = RayColor(ray, world);
            WriteColor(std::cout, pixel);
        }
    }

    clog << "Done! You can open your file now :)\n";
    return 0;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
