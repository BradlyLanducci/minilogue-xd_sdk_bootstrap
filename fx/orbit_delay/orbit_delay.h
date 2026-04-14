#pragma once

//--------------------------------------------------------------------------------

#include "time_audio_processor.h"

#include <userdelfx.h>
#include <delayline.hpp>

//--------------------------------------------------------------------------------

class OrbitDelay : public TimeAudioProcessor
{
public:
    explicit OrbitDelay(f32pair_t *p_ram, int size);

    void processFrame(float &xL, float &xR) override;

private:
    dsp::DualDelayLine m_delay;
};

//--------------------------------------------------------------------------------
