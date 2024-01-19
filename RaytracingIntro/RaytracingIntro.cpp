// RaytracingIntro.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Camera.h"
#include "HitableCollection.h"
#include "Sphere.h"
#include "MetalMaterial.h"
#include "LambertianMaterial.h"
#include "Dielectric.h"

using namespace std;

int main(int argc, char* argv[])
{
    //World
    HitableCollection world;

    shared_ptr<Material> groundMat = make_shared<LambertianMaterial>(Color(0.5, 0.5, 0.5));
    world.Add(make_shared<Sphere>(Position(0.0, -1000, -1.0), 1000, groundMat));

    for (int a = -7; a < 7; a++) {
        for (int b = -7; b < 7; b++) {
            clog << a << " " << b;
            double chooseMat = RandomDouble();
            Position center(a + 0.9 * RandomDouble(), 0.2, b + 0.9 * RandomDouble());

            if ((center - Position(4, 0.2, 0)).Length() > 0.9) {
                shared_ptr<Material> sphereMat;

                if (chooseMat < 0.8) {
                    Color albedo = Color::Random() * Color::Random();
                    sphereMat = make_shared<LambertianMaterial>(albedo);
                    world.Add(make_shared<Sphere>(center, 0.2, sphereMat));
                }
                else if (chooseMat < 0.95) {
                    Color albedo = Color::Random(0.5, 1);
                    double fuzz = RandomDouble(0, 0.5);
                    sphereMat = make_shared<MetalMaterial>(albedo, fuzz);
                    world.Add(make_shared<Sphere>(center,0.2,sphereMat));
                }
                else {
                    sphereMat = make_shared<Dielectric>(1.5);
                    world.Add(make_shared<Sphere>(center, 0.2, sphereMat));
                }
            }
        }
    }

    shared_ptr<Material> material1 = make_shared<Dielectric>(1.5);
    world.Add(make_shared<Sphere>(Position(0, 1, 0), 1.0, material1));

    shared_ptr<Material> material2 = make_shared<LambertianMaterial>(Color(0.4, 0.2, 0.1));
    world.Add(make_shared<Sphere>(Position(-4, 1, 0), 1.0, material2));

    shared_ptr<Material> material3 = make_shared<MetalMaterial>(Color(0.7, 0.6, 0.5), 0.0);
    world.Add(make_shared<Sphere>(Position(4, 1, 0), 1.0, material3));


    Camera camera(400, 16.0 / 9.0, 100, 50,20);
    camera.camPosition = Position(13, 2, 3);
    camera.target = Position(0, 0, 0);
    camera.camUp = Vector3(0, 1, 0);
    camera.defocusAngle = 0.6;
    camera.focusDist = 10.0;
    camera.Render(world);
    return 0;

}