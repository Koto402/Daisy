#include "daisy_pod.h"
#include "daisysp.h"
#include <stdio.h>
#include <string.h>

using namespace daisy;
using namespace daisysp;

DaisyPod   hw;

void AudioCallback(AudioHandle::InterleavingInputBuffer  in,
                   AudioHandle::InterleavingOutputBuffer out,
                   size_t                                size)
{
    for(size_t i = 0; i < size; i += 2)
    {
    }
}

int main(void)
{
    // Init
    hw.Init();
    hw.SetAudioBlockSize(4);
    System::Delay(250);

    for(;;)
    {
    }
}