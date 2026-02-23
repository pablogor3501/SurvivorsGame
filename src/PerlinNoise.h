// PerlinNoise.h

#ifndef PERLINNOISE_H 
#define PERLINNOISE_H 
#include <cmath>

class PerlinNoise
{
public:
    PerlinNoise(int seed = 2001);

    double perlin2D(double x, double y, double freq, int depth);

private:
    int seed;

    int noise2(int x, int y);
    double linInter(double x, double y, double s);
    double smoothInter(double x, double y, double s);
    double noise2D(double x, double y);

    static const unsigned char HASH[256];
};

#endif