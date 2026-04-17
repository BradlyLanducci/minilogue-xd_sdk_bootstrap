#pragma once

//--------------------------------------------------------------------------------

#include "vlsdk.h"

#include "userdelfx.h"

//--------------------------------------------------------------------------------

BEGIN_VLSDK_NAMESPACE

//--------------------------------------------------------------------------------

/// @brief 2.375 MB
constexpr uint32_t MaxMemoryPoolBytes{ 2 * 1024 * 1024 };

class MemoryPool
{
public:
    /// @brief We have 2.375 MB of sdram available so we allocate 1MB of it.

    static uint8_t *getMemory(uint32_t size);

private:
    static inline __sdram uint8_t m_pool[MaxMemoryPoolBytes];
    static inline uint32_t m_memoryIndex{};
};

//--------------------------------------------------------------------------------

END_VLSDK_NAMESPACE

//--------------------------------------------------------------------------------
