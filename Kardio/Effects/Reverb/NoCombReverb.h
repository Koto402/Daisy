#pragma once

#include <stdint.h>
#include <stdlib.h>
#include "DelayLine.h"
#include "LpfComb.h"
#include "DiffusionStep.h"
#include <array>

namespace kardio
{

template <typename T, size_t channels = 4, size_t steps = 4>
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
    std::array<DiffusionStep<T, channels>, steps> _DiffusionSteps;
};


void NoCombReverb<float, channels, steps>::Init(float fSampleRate)
{
  for(int i = 0; i < steps; i++)
  {
    _DiffusionSteps[i].Init(_fSampleRate);
  }
}

void NoCombReverb<float, channels, steps>::Process(const float x1, const float x2, float *y1, float *y2)
{
  float fOutput = 0.0f;
  std::array<float, channels> temp;
  temp.fill((x1+x2)*0.5);  //Split inputs into various signals 
  
  // Input -> Diffusion step 1 -> Diffusion step 2 -> Diffusion step n -> output
  for(int i = 0; i < steps; i++)
  {
    temp = _DiffusionSteps[i].Process(temp);
  }
  
  //Recombine outputs into single (stereo) sample
  for(int i = 0; i < channels; i++)
  {
    fOutput += temp[i];
  }
  *y1 = fOutput * (1/channels);
  *y2 = *y1;
}

}