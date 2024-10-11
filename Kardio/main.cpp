#include "daisy_pod.h"
#include "daisysp.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
//#include "Effects/Reverb/Reverb.h"
#include "Effects/Reverb/NoCombReverb.h"

using namespace daisy;
using namespace daisysp;
using namespace kardio;

#define SAMPLE_RATE 48000
#define BLOCK_SIZE 32

DaisyPod hw;
NoCombReverb verb;
Oscillator osc;
AdEnv env;
Parameter DryControl;
CpuLoadMeter CpuMeasure;

char sumbuff[128];
uint32_t ui32TransmitLength = 0;

void UsbCallback(uint8_t* buf, uint32_t* len)
{
    for(uint32_t i = 0; i < *len; i++)
    {
        sumbuff[i] = buf[i];
    }
    
    float fValue = strtof(&sumbuff[1], NULL); 
    char cCmd = sumbuff[0];
    sprintf(sumbuff, "Command: %c, Value: %.3f",cCmd, fValue);
    hw.seed.usb_handle.TransmitInternal((uint8_t*)sumbuff, strlen(sumbuff));
    verb.UartCallback(cCmd,fValue);
}

void Callback(void* data)
{            
    float fMax = CpuMeasure.GetMaxCpuLoad();
    float fMin = CpuMeasure.GetMinCpuLoad();
    float fAvg = CpuMeasure.GetAvgCpuLoad();
    sprintf(sumbuff,"Cpu load avg: %.2f, Min: %.2f, Max: %.2f \r\n", fAvg, fMin, fMax);
    hw.seed.usb_handle.TransmitInternal((uint8_t*)sumbuff, strlen(sumbuff));
}

void AudioCallback(AudioHandle::InterleavingInputBuffer in, AudioHandle::InterleavingOutputBuffer out, size_t size)
{
    CpuMeasure.OnBlockStart();
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

    CpuMeasure.OnBlockEnd();
}

int main(void)
{
    TimerHandle         tim5;
    TimerHandle::Config tim_cfg;

    hw.Init();   
    hw.SetAudioBlockSize(BLOCK_SIZE);
    hw.StartAudio(AudioCallback);
    hw.StartAdc();
    CpuMeasure.Init(SAMPLE_RATE,BLOCK_SIZE);
    
    hw.seed.usb_handle.Init(UsbHandle::FS_INTERNAL);
    hw.seed.usb_handle.SetReceiveCallback(UsbCallback, UsbHandle::FS_INTERNAL);
    hw.led1.Set(0,0.2f,0);
  
    /** TIM5 with IRQ enabled */
    tim_cfg.periph     = TimerHandle::Config::Peripheral::TIM_5;
    tim_cfg.enable_irq = true;
    auto tim_target_freq = 0.1f; //0.1 should be once every 10 seconds it is however once every 5 seconds
    auto tim_base_freq   = System::GetPClk2Freq();
    tim_cfg.period       = tim_base_freq / tim_target_freq;

    tim5.Init(tim_cfg);
    tim5.SetCallback(Callback);
    tim5.Start();

    verb.Init(SAMPLE_RATE);
    System::Delay(1000);

    while(1)
    {
        hw.led1.Update();
    } 
}


