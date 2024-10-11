#pragma once

#include <stdint.h>

class DiffusionStep
{
    public:

    DiffusionStep() {};
    ~DiffusionStep() {};

    void Init(float fSampleRate)
        {
            _fSampleRate = fSampleRate;
            _ui32Delay = 0;
            _ui32Write = 0;
            _fFeedback = 0.5f;
        }


    private:
    float _fSampleRate;
    float _fFeedback;
    uint32_t _ui32Delay;
    uint32_t _ui32Write;
}