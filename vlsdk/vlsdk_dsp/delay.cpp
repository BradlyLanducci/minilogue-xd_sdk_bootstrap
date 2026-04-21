#include "vlsdk_dsp/delay.h"
#include "vlsdk_utilities/memory_pool.h"

#include <cstring>

//--------------------------------------------------------------------------------

BEGIN_VLSDK_NAMESPACE

//--------------------------------------------------------------------------------

Delay::Delay(uint32_t size)
    : mp_buffer(reinterpret_cast<f32pair_t *>(MemoryPool::getMemory(size * sizeof(f32pair_t))))
    , m_bitMask(size - 1)
{
}

//--------------------------------------------------------------------------------

void Delay::clear()
{
    memset(mp_buffer, 0, (m_bitMask + 1) * sizeof(f32pair_t));
}

//--------------------------------------------------------------------------------

void Delay::write(f32pair_t sample)
{
    mp_buffer[m_writeIdx-- & m_bitMask] = sample;
}

//--------------------------------------------------------------------------------

f32pair_t Delay::read(uint32_t offset)
{
    return mp_buffer[(m_writeIdx + offset) & m_bitMask];
}

//--------------------------------------------------------------------------------

f32pair_t Delay::readFrac(float offset)
{
    uint32_t base{ static_cast<uint32_t>(offset) };
    float frac{ offset - static_cast<float>(base) };
    f32pair_t x0{ read(base) };
    f32pair_t x1{ read(base + 1) };
    return lerpF32Pair(x0, x1, frac);
}

//--------------------------------------------------------------------------------

float Delay::lerp(float a, float b, float frac) const
{
    return a + frac * (b - a);
}

//--------------------------------------------------------------------------------

f32pair_t Delay::lerpF32Pair(const f32pair_t &x0, const f32pair_t &x1, float frac) const
{
    return f32pair_t{ lerp(x0.a, x1.a, frac), lerp(x0.b, x1.b, frac) };
}

//--------------------------------------------------------------------------------

END_VLSDK_NAMESPACE

//--------------------------------------------------------------------------------
