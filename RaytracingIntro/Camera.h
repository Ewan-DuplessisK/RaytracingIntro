#pragma once

#include "Color.h"
#include "Hitable.h"

class Camera{ // Prend le rôle de l'ancien main

public:
	Camera() = default;
	Camera(double imgWidth,double ratio, int samplePerPixel = 10, int bounces = 10):aspectRatio(ratio),width(imgWidth),sampleCount(samplePerPixel),maxBounces(bounces){}
	void Render(const Hitable& rWorld);

private:
	int height;
	double aspectRatio, width;
	int sampleCount,maxBounces;
	Position center, originPixelLocation;
	Vector3 pixelDeltaX, pixelDeltaY;

	void Initialize();
	Color RayColor(const Ray& rRay,int bouncesLeft, const Hitable& rWorld) const;
	Ray GetRay(int x, int y) const;
	Vector3 PixelSampleSquared() const;

};
