#pragma once

namespace le 
{

class Maths
{
public:
    static float GetRandomFloat(float _minum = 0.0, float _maximum = 1.0);
    static float ReprojectRange(float xi1, float xi2, float xf1, float xf2, float x);    
};

}