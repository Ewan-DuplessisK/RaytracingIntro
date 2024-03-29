#pragma once
#include "Vector3.h"
#include "Interval.h"

//New Vector3 alias for color
using Color = Vector3;

inline double toGamma(double linear) {
    return sqrt(linear);
}

inline void WriteColor(std::ostream& out, Color pixel, int sampleCount){

    double scale = 1.0 / sampleCount;
    double r = toGamma(pixel.x * scale);
    double g = toGamma(pixel.y * scale);
    double b = toGamma(pixel.z * scale);

    // Write the translated [0,255] value of each color component.
    static const Interval intensity(0.000, 0.999);
    out << static_cast<int>(255.999 * intensity.Clamp(r)) << ' '
        << static_cast<int>(255.999 * intensity.Clamp(g)) << ' '
        << static_cast<int>(255.999 * intensity.Clamp(b)) << '\n';
}

