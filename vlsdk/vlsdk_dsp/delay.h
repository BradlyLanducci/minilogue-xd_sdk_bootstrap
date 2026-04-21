#pragma once

#include "float_math.h"

#include "vlsdk.h"

//--------------------------------------------------------------------------------

BEGIN_VLSDK_NAMESPACE

//--------------------------------------------------------------------------------

/*
    Stealing this from their code, so I can make it constexpr.
*/
constexpr uint32_t nextPow2U32(uint32_t x)
{
    x--;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    return ++x;
}

//--------------------------------------------------------------------------------

class Delay
{
public:
    Delay(uint32_t size);

    void clear();

    void write(f32pair_t sample);

    f32pair_t read(uint32_t offset);
    f32pair_t readFrac(float offset);

private:
    float lerp(float a, float b, float frac) const;
    f32pair_t lerpF32Pair(const f32pair_t &x0, const f32pair_t &x1, float frac) const;

    uint32_t m_writeIdx{ 0 };
    uint32_t m_bitMask{ 0 };
    f32pair_t *mp_buffer{ nullptr };
};

//--------------------------------------------------------------------------------

END_VLSDK_NAMESPACE

//--------------------------------------------------------------------------------
