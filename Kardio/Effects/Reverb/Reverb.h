#pragma once

#include <stdint.h>
#include <stdlib.h>
#include "Allpass.h"
#include "DelayLine.h"
#include "LpfComb.h"
#include "Lowpass.h"

namespace kardio
{

class Reverb
{
  public:
    Reverb() {}
    ~Reverb() {}

    void Init(float fSampleRate);
    void Process(const float x1, const float x2, float *y1, float *y2);
    void UartCallback(char cCmd, float fValue);

  private:
    float _fSampleRate;
    LpfComb<float, 5000> _CombL1;
    LpfComb<float, 5000> _CombL2;
    LpfComb<float, 5000> _CombL3;
    LpfComb<float, 5000> _CombL4;
    LpfComb<float, 5000> _CombL5;
    LpfComb<float, 5000> _CombL6;
    Allpass<float, 5000> _ApL1;
    Allpass<float, 5000> _ApL2;
    Allpass<float, 5000> _ApL3;

    LpfComb<float, 5000> _CombR1;
    LpfComb<float, 5000> _CombR2;
    LpfComb<float, 5000> _CombR3;
    LpfComb<float, 5000> _CombR4;
    LpfComb<float, 5000> _CombR5;
    LpfComb<float, 5000> _CombR6;
    Allpass<float, 5000> _ApR1;
    Allpass<float, 5000> _ApR2;
    Allpass<float, 5000> _ApR3;
    Lowpass _LpfL1;
    Lowpass _LpfL2;
    Lowpass _LpfR1;
    Lowpass _LpfR2;

};

}