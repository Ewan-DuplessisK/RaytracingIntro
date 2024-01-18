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

private:
	int height;
	double aspectRatio, width;
	int sampleCount,maxBounces;
	Position center, originPixelLocation;
	Vector3 pixelDeltaX, pixelDeltaY;
	Vector3 u, v, w;


	void Initialize();
	Color RayColor(const Ray& rRay,int bouncesLeft, const Hitable& rWorld) const;
	Ray GetRay(int x, int y) const;
	Vector3 PixelSampleSquared() const;

};
