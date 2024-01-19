#pragma once

#include "Color.h"
#include "Hitable.h"

class Camera{ // Prend le rôle de l'ancien main

public:
	Camera() = default;
	Camera(double imgWidth,double ratio, int samplePerPixel = 10, int bounces = 10,double fov=90):aspectRatio(ratio),width(imgWidth),sampleCount(samplePerPixel),maxBounces(bounces),vfov(fov){}
	void Render(const Hitable& rWorld);
	double vfov;  // Vertical view angle (field of view)
	Position camPosition = Position(0, 0, -1);
	Position target = Position(0, 0, 0);
	Vector3 camUp = Vector3(0, 1, 0);
	double defocusAngle = 0;  // Variation angle of rays through each pixel
	double focusDist = 10;    // Distance from camera lookfrom point to plane of perfect focus

private:
	int height;
	double aspectRatio, width;
	int sampleCount,maxBounces;
	Position center, originPixelLocation;
	Vector3 pixelDeltaX, pixelDeltaY;
	Vector3 u, v, w;
	Vector3 DefocusDiskX;  // Defocus disk horizontal radius
	Vector3 DefocusDiskY;  // Defocus disk vertical radius


	void Initialize();
	Color RayColor(const Ray& rRay,int bouncesLeft, const Hitable& rWorld) const;
	Ray GetRay(int x, int y) const;
	Vector3 PixelSampleSquared() const;
	Position DefocusSample() const;

};
