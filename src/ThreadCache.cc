#include "ThreadCache.h"
namespace MemoryPool
{

    void *ThreadCache::allocate(size_t index)
    {
        return nullptr;
    }

    void ThreadCache::deallocate(void *ptr, size_t size)
    {
    }

    void *ThreadCache::fetchFromCenterCache(size_t index)
    {
        return nullptr;
    }

    void ThreadCache::returnToCenterCache(void *start, size_t size, size_t bytes)
    {
    }
}