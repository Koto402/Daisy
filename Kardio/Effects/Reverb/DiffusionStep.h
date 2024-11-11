#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <array> 
#include "DelayLine.h"

namespace kardio
{

template<typename T, size_t channels = 4>
class DiffusionStep
{
  public:

    DiffusionStep() {};
    ~DiffusionStep() {};
    void Init(float fSampleRate);
    std::array<T, channels> Process(std::array<T, channels> input);

  private:
    float _fSampleRate;
    std::array<DelayLine, channels> delays;
};

void DiffusionStep<float, channels>::Init(float fSampleRate)
{
    _fSampleRate = fSampleRate;
}

std::array<float, channels> DiffusionStep<float, channels>::Process(std::array<float, channels> input)
{
    std::array<float, channels> output;
    for(int i = 0; i < channels; i++)
    {
        delays[i].Process(input, &output[i]);
    }
    return output;
}


}