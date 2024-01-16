// RaytracingIntro.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Camera.h"
#include "HitableCollection.h"
#include "Sphere.h"
#include "MetalMaterial.h"
#include "LambertianMaterial.h"

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



int main(int argc, char* argv[])
{
    //World
    HitableCollection world;

    shared_ptr<Material> groundMat = make_shared<LambertianMaterial>(Color(0.8, 0.8, 0.0));
    shared_ptr<Material> centerMat = make_shared<LambertianMaterial>(Color(0.7, 0.3, 0.3));
    shared_ptr<Material> leftMat = make_shared<MetalMaterial>(Color(0.8, 0.8, 0.8));
    shared_ptr<Material> rightMat = make_shared<MetalMaterial>(Color(0.8, 0.6, 0.2));

    world.Add(make_shared<Sphere>(Position(0, -100.5, -1), 100, groundMat));
    world.Add(make_shared<Sphere>(Position(0, 0, -1), 0.5, centerMat));
    world.Add(make_shared<Sphere>(Position(-1.0, 0, -1), 0.5, leftMat));
    world.Add(make_shared<Sphere>(Position(1.0, 0, -1), 0.5, rightMat));


    Camera camera(400, 16.0 / 9.0, 100, 50);
    camera.Render(world);
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
