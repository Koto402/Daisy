#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "Reverb.h"

using namespace kardio;

void Reverb::Init(float fSampleRate)
{
    _fSampleRate = fSampleRate;
    _CombL1.Init(_fSampleRate);
    _CombL1.SetFeedback(0.46f);
    _CombL1.SetLpfGain(0.4482f);
    _CombL1.SetDelayMs(50);

    _CombL2.Init(_fSampleRate);
    _CombL2.SetFeedback(0.47f);
    _CombL2.SetLpfGain(0.4399f);
    _CombL2.SetDelayMs(56);

    _CombL3.Init(_fSampleRate);
    _CombL3.SetFeedback(0.475f);
    _CombL3.SetLpfGain(0.4350f);
    _CombL3.SetDelayMs(61);

    _CombL4.Init(_fSampleRate);
    _CombL4.SetFeedback(0.48);
    _CombL4.SetLpfGain(0.4316f);
    _CombL4.SetDelayMs(68);

    _CombL5.Init(_fSampleRate);
    _CombL5.SetFeedback(0.49f);
    _CombL5.SetLpfGain(0.4233f);
    _CombL5.SetDelayMs(72);

    _CombL6.Init(_fSampleRate);
    _CombL6.SetFeedback(0.50f);
    _CombL6.SetLpfGain(0.3735f);
    _CombL6.SetDelayMs(78);

    _ApL1.Init(_fSampleRate);
    _ApL1.SetGain(0.7f);
    _ApL1.SetDelayMs(1);
    _ApL2.Init(_fSampleRate);
    _ApL2.SetGain(0.7f);
    _ApL2.SetDelayMs(2);
    _ApL3.Init(_fSampleRate);
    _ApL3.SetGain(0.7f);
    _ApL3.SetDelayMs(9);

    _CombR1.Init(_fSampleRate);
    _CombR1.SetFeedback(0.46f);
    _CombR1.SetLpfGain(0.4482f);
    _CombR1.SetDelayMs(50);

    _CombR2.Init(_fSampleRate);
    _CombR2.SetFeedback(0.47f);
    _CombR2.SetLpfGain(0.4399f);
    _CombR2.SetDelayMs(56);

    _CombR3.Init(_fSampleRate);
    _CombR3.SetFeedback(0.475f);
    _CombR3.SetLpfGain(0.4350f);
    _CombR3.SetDelayMs(61);

    _CombR4.Init(_fSampleRate);
    _CombR4.SetFeedback(0.48);
    _CombR4.SetLpfGain(0.4316f);
    _CombR4.SetDelayMs(68);

    _CombR5.Init(_fSampleRate);
    _CombR5.SetFeedback(0.49f);
    _CombR5.SetLpfGain(0.4233f);
    _CombR5.SetDelayMs(72);

    _CombR6.Init(_fSampleRate);
    _CombR6.SetFeedback(0.50f);
    _CombR6.SetLpfGain(0.3735f);
    _CombR6.SetDelayMs(78);

    _ApR1.Init(_fSampleRate);
    _ApR1.SetGain(0.5f);
    _ApR1.SetDelayMs(7);
    _ApR2.Init(_fSampleRate);
    _ApR2.SetGain(0.5f);
    _ApR2.SetDelayMs(10);
    _ApR3.Init(_fSampleRate);
    _ApR3.SetGain(0.7f);
    _ApR3.SetDelayMs(9);

    _LpfL1.Init(_fSampleRate, 6000.0f);
    _LpfL2.Init(_fSampleRate, 4000.0f);
    _LpfR1.Init(_fSampleRate, 6000.0f);
    _LpfR2.Init(_fSampleRate, 4000.0f);
}

void Reverb::Process(const float x1, const float x2, float *y1, float *y2)
{
    float fRead = 0.0f;
    float fTemp = 0.0f;
    float fApInput = 0.0f;
    float fLpfOut = 0.0f;
    float fGainModifier = 0.33f;

    _LpfL1.Process(x1, &fLpfOut);
    _ApL1.Process(fLpfOut, &fApInput);
    _ApL2.Process(fApInput, &fApInput);

    _CombL1.Process(fApInput, &fRead);
    fTemp += fRead * fGainModifier;
    _CombL2.Process(fApInput, &fRead);
    fTemp += fRead * -fGainModifier;
    _CombL3.Process(fApInput, &fRead);
    fTemp += fRead * fGainModifier;
    _CombL4.Process(fApInput, &fRead);
    fTemp += fRead * -fGainModifier;
    _CombL5.Process(fApInput, &fRead);
    fTemp += fRead * fGainModifier;
    _CombL6.Process(fApInput, &fRead);
    fTemp += fRead * -fGainModifier;

    _LpfL2.Process(fTemp,&fLpfOut);


    _ApL3.Process(fLpfOut, y1);

    fRead = 0.0f;
    fTemp = 0.0f;
    fApInput = 0.0f;
    fLpfOut = 0.0f;

    _LpfR1.Process(x2, &fLpfOut);
    _ApR1.Process(fLpfOut, &fApInput);
    _ApR2.Process(fApInput, &fApInput);

    _CombR1.Process(fApInput, &fRead);
    fTemp += fRead * fGainModifier;
    _CombR2.Process(fApInput, &fRead);
    fTemp += fRead * -fGainModifier;
    _CombR3.Process(fApInput, &fRead);
    fTemp += fRead * fGainModifier;
    _CombR4.Process(fApInput, &fRead);
    fTemp += fRead * -fGainModifier;
    _CombR5.Process(fApInput, &fRead);
    fTemp += fRead * fGainModifier;
    _CombR6.Process(fApInput, &fRead);
    fTemp += fRead * -fGainModifier;

    _LpfL2.Process(fTemp,&fLpfOut);
    _ApL3.Process(fLpfOut, y2);
}

void Reverb::UartCallback(char cCmd, float fValue)
{
    switch(cCmd)
    {
        case 'a':
            _ApL1.SetDelayMs(fValue);
            _ApR1.SetDelayMs(fValue);
            break;
        case 'b':
            _ApL2.SetDelayMs(fValue);
            _ApR2.SetDelayMs(fValue);
            break;
        case 'c':
            _ApL3.SetDelayMs(fValue);
            _ApR3.SetDelayMs(fValue);
            break;
        case 'd':
            _LpfL1.SetCutoff(fValue);
            _LpfR1.SetCutoff(fValue);
            break;
        case 'e':
            _LpfL2.SetCutoff(fValue);
            _LpfR2.SetCutoff(fValue);
            break;
    }
}