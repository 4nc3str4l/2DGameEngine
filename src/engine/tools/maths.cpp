#include "maths.h"

#include<iostream>

namespace le 
{

float Maths::GetRandomFloat(float _minimum, float _maximum)
{   
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = _maximum - _minimum;
    float r = random * diff;
    return _minimum + r;
}

float Maths::ReprojectRange(float xi1, float xi2, float xf1, float xf2, float x)
{
    return xf1 + ((x - xi1) / (xi2 - xi1)) * (xf2 - xf1);
}

}