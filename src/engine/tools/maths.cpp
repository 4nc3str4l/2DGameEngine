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

}