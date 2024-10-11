#pragma once
#ifndef DELAYLINE_H
#define DELAYLINE_H

#include <stdint.h>
#include <stdlib.h>

template<typename T, uint32_t ui32MaxSize>
class DelayLine
{
  public:
    DelayLine() {}
    ~DelayLine() {}

    void Init(uint32_t ui32SampleRate)
    {
        _ui32MaxSize = ui32MaxSize;
        _ui32SampleRate = ui32SampleRate;
        _ui32Delay = 0;
        _ui32Write = 0;
        _fFeedback = 0.5f;
        for (uint32_t i = 0; i < ui32MaxSize; i++)
        {
            _fDelayLine[i] = 0;
        }
    }

    void SetDelay(uint32_t ui32Delay)
    {
        if (ui32Delay < _ui32MaxSize)
        {
            _ui32Delay = ui32Delay;
        }   
        else 
        {
            _ui32Delay = _ui32MaxSize - 1;
        }
    }

    void SetDelayMs(uint32_t ui32DelayMs)
    {
        uint32_t ui32SampleDelay = _ui32SampleRate / 1000 * ui32DelayMs;
        if(ui32SampleDelay < _ui32MaxSize)
        {
            _ui32Delay = ui32SampleDelay;
        }
        else 
        {
            _ui32Delay = _ui32MaxSize - 1;
        }
    }

    void SetFeedback(float fFeedback)
    {
        if (fFeedback >= 0 && fFeedback <= 1)
        {
            _fFeedback = fFeedback;
        }
    }

    void Process(const float fIn, float *fOut)
    {
        Read(fOut);
        Write(fIn);
    }

    void Read(float *fOut)
    {
        uint32_t ui32Read = (_ui32Write - _ui32Delay + _ui32MaxSize) % _ui32MaxSize;
        *fOut = _fDelayLine[ui32Read];
    }

    void Write(const float fIn)
    {
        uint32_t ui32Read = (_ui32Write - _ui32Delay + _ui32MaxSize) % _ui32MaxSize;
        _fDelayLine[_ui32Write] = fIn +  _fDelayLine[ui32Read] * _fFeedback;
        _ui32Write = (_ui32Write + 1) % _ui32MaxSize;
    }

  private:
    float _fFeedback;
    uint32_t _ui32MaxSize;
    uint32_t _ui32Write;
    uint32_t _ui32Delay;
    uint32_t _ui32SampleRate;
    T _fDelayLine[ui32MaxSize];
};

#endif //DELAYLINE_H