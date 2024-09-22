#pragma once

#include <stdint.h>
#include "math.h"

namespace kardio
{

#define PI       3.14159265359f

class Lowpass
{
  public:
    Lowpass() {}
    ~Lowpass() {}

    void Init(float fSampleRateIn, float fCutoff)
    {
        fPrevSample = 0.0f;
        fA0 = 0.0f;
        fB1 = 0.0f;
        fSampleRate = fSampleRateIn;
        SetCutoff(fCutoff);
    }
    void Process(const float x1, float *y1)
    {
        *y1 = x1 * fA0 + fPrevSample * (-fB1);
        fPrevSample = *y1;
    }
    void SetCutoff(float fCutoff)
    {
        float fTheta = 2.0f * PI * (fCutoff / fSampleRate);
        float fGamma = 2.0f - cosf(fTheta);
        fB1 = sqrtf(powf(fGamma, 2) - 1.0f) - fGamma;
        fA0 = 1.0f + fB1;
    }

  private:
    float fSampleRate;
    float fPrevSample;
    float fA0;
    float fB1;
};

}
