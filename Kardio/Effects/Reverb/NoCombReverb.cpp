#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "NoCombReverb.h"

using namespace kardio;

//Divided by 4 to account for summing of signal later
float fHadamard[] = {
    1.0f, 1.0f, 1.0f, -1.0f
};

void NoCombReverb::Init(float fSampleRate)
{
    _fSampleRate = fSampleRate;
    
    _Ch1.Init(_fSampleRate);
    _Ch1.SetDelay(821);
    _Ch1.SetFeedback(0.5f);
    _Ch2.Init(_fSampleRate);
    _Ch2.SetDelay(883);
    _Ch2.SetFeedback(0.5f);
    _Ch3.Init(_fSampleRate);
    _Ch3.SetDelay(1231);
    _Ch3.SetFeedback(0.5f);
    _Ch4.Init(_fSampleRate);
    _Ch4.SetDelay(1627);
    _Ch4.SetFeedback(0.5f);

    _Ch5.Init(_fSampleRate);
    _Ch5.SetDelay(2713);
    _Ch5.SetFeedback(0.5f);
    _Ch6.Init(_fSampleRate);
    _Ch6.SetDelay(2843);
    _Ch6.SetFeedback(0.5f);
    _Ch7.Init(_fSampleRate);
    _Ch7.SetDelay(4073);
    _Ch7.SetFeedback(0.5f);
    _Ch8.Init(_fSampleRate);
    _Ch8.SetDelay(3943);
    _Ch8.SetFeedback(0.5f);



/*
    _LpfComb1.Init(_fSampleRate);
    _LpfComb1.SetDelay(421);
    _LpfComb1.SetFeedback(0.4f);
    _LpfComb2.Init(_fSampleRate);
    _LpfComb2.SetDelay(727);
    _LpfComb2.SetFeedback(0.4f);
    _LpfComb3.Init(_fSampleRate);
    _LpfComb3.SetDelay(1069);
    _LpfComb3.SetFeedback(0.4f);
    _LpfComb4.Init(_fSampleRate);
    _LpfComb4.SetDelay(1223);
    _LpfComb4.SetFeedback(0.4f);
*/
}

void NoCombReverb::Process(const float x1, const float x2, float *y1, float *y2)
{
    //Split into N channels
    float fCh1Sig = x1;
    float fCh2Sig = x2;
    float fCh3Sig = x1;
    float fCh4Sig = x2;

    float fTemp1 = 0.0f;
    float fTemp2 = 0.0f;
    float fTemp3 = 0.0f;
    float fTemp4 = 0.0f;

    float fTemp5 = 0.0f;
    float fTemp6 = 0.0f;
    float fTemp7 = 0.0f;
    float fTemp8 = 0.0f;

    _Ch1.Process(fCh1Sig, &fTemp1);
    _Ch2.Process(fCh2Sig, &fTemp2);
    _Ch3.Process(fCh3Sig, &fTemp3);
    _Ch4.Process(fCh4Sig, &fTemp4);

    fTemp1 *=  1; 
    fTemp2 *= -1;
    fTemp3 *=  1; 
    fTemp4 *= -1;

    _Ch5.Process(fCh1Sig, &fTemp5);
    _Ch6.Process(fCh2Sig, &fTemp6);
    _Ch7.Process(fCh3Sig, &fTemp7);
    _Ch8.Process(fCh4Sig, &fTemp8);




    /*
    //Repeat diffusion steps
    for(uint32_t i = 0; i < 1; i++)
    {
        //Delay each channel
        //_Ch3.Process(fCh3Sig, &fTemp3);
        //_Ch4.Process(fCh4Sig, &fTemp4);

        //Shuffle and invert channels
        //Hadamard matrix (unitary matrix)
        //fCh3Sig = fTemp1 * fHadamard[2];
        //fCh4Sig = fTemp3 * fHadamard[3];
    }
    */
    //Comb filter with Householder matrix step
    //_LpfComb1.Process(fCh1Sig,&fCh1Sig);
    //_LpfComb2.Process(fCh2Sig,&fCh2Sig);
    //_LpfComb3.Process(fCh3Sig,&fCh3Sig);
    //_LpfComb4.Process(fCh4Sig,&fCh4Sig);

    //Mix down from N channels
    *y1 = (fTemp5 + fTemp6);
    *y2 = (fTemp7 + fTemp8);
}

void NoCombReverb::UartCallback(char cCmd, float fValue)
{
    switch(cCmd)
    {
        default:
            break;
    }
}