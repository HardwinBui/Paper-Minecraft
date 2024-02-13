#ifndef PERLIN_H
#define PERLIN_H

#include <math.h>
#include <cstdlib>
#include <stdio.h>
#include <time.h>

typedef struct {
    float x, y;
} vector2;

const float scaleUV = 10.0f;

class Perlin
{
public:
    Perlin();
    float PerlinNoise(float x, float y);

private:
    float xShift;
    float Interpolate(float a0, float a1, float w);
    vector2 RandomGradient(int ix, int iy);
    float DotGridGradient(int ix, int iy, float x, float y);
};


#endif