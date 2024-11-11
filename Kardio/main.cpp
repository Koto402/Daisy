#include "daisy_seed.h"
#include "daisysp.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

using namespace daisy;
using namespace daisysp;

DaisySeed hw;
daisy::TimerHandle Tim5Handle;

/** @brief User Callback type that will fire at the end of each timer 
 *   period. This requires that Config::enable_irq is true before Init
 *  @param data pointer to arbitrary user-provided data
*/
void Tim5Callback(void* data)
{
    uint16_t outputValue = (uint16_t)((rand() % (4095 + 1)));
    hw.dac.WriteValue(DacHandle::Channel::BOTH, outputValue);
    return;
}

void InitTimer(daisy::TimerHandle timerHandle, daisy::TimerHandle::PeriodElapsedCallback cb, daisy::TimerHandle::Config::Peripheral timer, float targetFrequency, bool enableIrq)
{
    TimerHandle::Config timerCfg;

    /** TIM5 with IRQ enabled */
    timerCfg.periph     = timer;
    timerCfg.enable_irq = enableIrq;
    timerCfg.period     = (System::GetPClk2Freq() / targetFrequency) * 2;

    /** Initialize timer */
    timerHandle.Init(timerCfg);
    timerHandle.SetCallback(cb);
    /** Start the timer, and generate callbacks at the end of each period */
    timerHandle.Start();
}

int main(void)
{
    bool led_state = TRUE;
    hw.Configure();
    hw.Init();
    // init DAC outputs
	DacHandle::Config cfg;
	cfg.bitdepth = DacHandle::BitDepth::BITS_12;
	cfg.buff_state = DacHandle::BufferState::ENABLED;
	cfg.mode = DacHandle::Mode::POLLING;
	cfg.chn = DacHandle::Channel::BOTH;
	hw.dac.Init(cfg);

    InitTimer(Tim5Handle, Tim5Callback, daisy::TimerHandle::Config::Peripheral::TIM_5, 1, true);

    while(1)
    {
        hw.SetLed(led_state);
        hw.DelayMs(1000);

        // Toggle the LED state for the next time around.
        led_state = !led_state;
    } 
}