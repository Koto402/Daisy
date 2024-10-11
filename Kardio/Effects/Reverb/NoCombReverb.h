#pragma once

#include <stdint.h>
#include <stdlib.h>
#include "DelayLine.h"
#include "LpfComb.h"

namespace kardio
{

class NoCombReverb
{
  public:
    NoCombReverb() {}
    ~NoCombReverb() {}

    void Init(float fSampleRate);
    void Process(const float x1, const float x2, float *y1, float *y2);
    void UartCallback(char cCmd, float fValue);

  private:
    float _fSampleRate;   
    DelayLine<float, 5000> _Ch1;
    DelayLine<float, 5000> _Ch2;
    DelayLine<float, 5000> _Ch3;
    DelayLine<float, 5000> _Ch4;

    DelayLine<float, 5000> _Ch5;
    DelayLine<float, 5000> _Ch6;
    DelayLine<float, 5000> _Ch7;
    DelayLine<float, 5000> _Ch8;

    LpfComb<float, 5000> _LpfComb1;
    LpfComb<float, 5000> _LpfComb2;
    LpfComb<float, 5000> _LpfComb3;
    LpfComb<float, 5000> _LpfComb4;
};

}