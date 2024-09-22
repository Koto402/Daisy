#include "daisy_pod.h"
#include "daisysp.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "Effects/Reverb/Reverb.h"

using namespace daisy;
using namespace daisysp;
using namespace kardio;

#define SAMPLE_RATE 48000

DaisyPod hw;
Reverb verb;
Oscillator osc;
AdEnv env;
Parameter DryControl;

char sumbuff[1024];
static bool bTransmit = false;
uint32_t ui32TransmitLength = 0;

void UsbCallback(uint8_t* buf, uint32_t* len)
{
    //verb.UartCallback(&buf[0], 1);
    for(uint32_t i = 0; i < *len; i++)
    {
        sumbuff[i] = buf[i];
    }
    bTransmit = true;
}


void AudioCallback(AudioHandle::InterleavingInputBuffer in, AudioHandle::InterleavingOutputBuffer out, size_t size)
{
    float fWetL = 0;
    float fWetR = 0;
    float fWetControl = 0;
    static bool bPlayDryAudio = false;

    hw.ProcessDigitalControls();
    hw.ProcessAnalogControls();
    fWetControl = hw.knob1.Process();

    if(hw.button2.RisingEdge())
    {
        bPlayDryAudio = !bPlayDryAudio;
        if(bPlayDryAudio == false)
        {
            hw.led1.SetGreen(0.2f);
        }
        else
        {
            hw.led1.SetGreen(0);    
        }
    }

    for(size_t i = 0; i < size; i+=2)
    {
        if(bPlayDryAudio == false)
        {
            verb.Process(in[i], in[i+1], &fWetL, &fWetR);
            out[i]     = ((1-fWetControl) * in[i])   + (fWetControl * fWetL);
            out[i + 1] = ((1-fWetControl) * in[i+1]) + (fWetControl * fWetR);
        }
        else
        {
            out[i]     = in[i];
            out[i + 1] = in[i+1];
        }
    }
}

int main(void)
{
    hw.Init();   
    hw.SetAudioBlockSize(4);
    hw.StartAudio(AudioCallback);
    hw.StartAdc();
    hw.seed.usb_handle.Init(UsbHandle::FS_INTERNAL);
    hw.seed.usb_handle.SetReceiveCallback(UsbCallback, UsbHandle::FS_INTERNAL);
    hw.led1.Set(0,0.2f,0);

    verb.Init(SAMPLE_RATE);
    System::Delay(1000);

    for(;;)
    {
        hw.led1.Update();

        if(bTransmit == true)
        {
            float fValue = strtof(&sumbuff[1], NULL); 
            char cCmd = sumbuff[0];
            sprintf(sumbuff, "Command: %c, Value: %.3f",cCmd, fValue);
            hw.seed.usb_handle.TransmitInternal((uint8_t*)sumbuff, strlen(sumbuff));
            bTransmit = false;
            verb.UartCallback(cCmd,fValue);
        }
    } 
}