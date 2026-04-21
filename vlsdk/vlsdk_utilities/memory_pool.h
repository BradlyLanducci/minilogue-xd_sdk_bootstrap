#pragma once

//--------------------------------------------------------------------------------

#include "vlsdk.h"

#include "userdelfx.h"

//--------------------------------------------------------------------------------

BEGIN_VLSDK_NAMESPACE

//--------------------------------------------------------------------------------

class MemoryPool
{
public:
    /// @brief 2 MB
    static inline constexpr uint32_t MaxMemoryPoolBytes{ 2 * 1024 * 1024 };

    static uint8_t *getMemory(uint32_t size);

private:
    static inline __sdram uint8_t m_pool[MaxMemoryPoolBytes];
    static inline uint32_t m_memoryIndex{};
};

//--------------------------------------------------------------------------------

END_VLSDK_NAMESPACE

//--------------------------------------------------------------------------------
