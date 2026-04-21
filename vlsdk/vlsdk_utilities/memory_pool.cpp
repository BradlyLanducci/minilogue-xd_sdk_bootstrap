#include "vlsdk_utilities/memory_pool.h"

//--------------------------------------------------------------------------------

BEGIN_VLSDK_NAMESPACE

//--------------------------------------------------------------------------------

uint8_t *MemoryPool::getMemory(uint32_t size)
{
    if (m_memoryIndex + size < MaxMemoryPoolBytes)
    {
        uint8_t *p_memory{ &m_pool[m_memoryIndex] };
        m_memoryIndex += size;
        return p_memory;
    }
    return nullptr;
}

//--------------------------------------------------------------------------------

END_VLSDK_NAMESPACE

//--------------------------------------------------------------------------------
