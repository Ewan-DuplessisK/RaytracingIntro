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

    shared_ptr<Material> groundMat = make_shared<LambertianMaterial>(Color(0.8, 0.8, 0.0));
    shared_ptr<Material> centerMat = make_shared<LambertianMaterial>(Color(0.1,0.2,0.5));
    shared_ptr<Material> leftMat = make_shared<Dielectric>(1.5);
    shared_ptr<Material> rightMat = make_shared<MetalMaterial>(Color(0.8, 0.6, 0.2), 0.0);

    world.Add(make_shared<Sphere>(Position(-1, 0, -1), -0.4, leftMat));
    world.Add(make_shared<Sphere>(Position(1, 0, -1), 0.5, rightMat));
    world.Add(make_shared<Sphere>(Position(0.0,-100.5,-1.0), 100, groundMat));
    world.Add(make_shared<Sphere>(Position(0, 0, -1), 0.5, centerMat));
    world.Add(make_shared<Sphere>(Position(-1, 0, -1), 0.5, leftMat));


    Camera camera(400, 16.0 / 9.0, 100, 50,90);
    camera.camPosition = Position(-2, 2, 1);
    camera.target = Position(0, 0, -1);
    camera.camUp = Vector3(0, 1, 0);
    camera.Render(world);
    return 0;

}