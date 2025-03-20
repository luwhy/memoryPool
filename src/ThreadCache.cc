#include "ThreadCache.h"

void *MemoryPool::ThreadCache::allocate(size_t index)
{
    return nullptr;
}

void MemoryPool::ThreadCache::deallocate(void *ptr, size_t size)
{
}

void *MemoryPool::ThreadCache::fetchFromCenterCache(size_t index)
{
    return nullptr;
}

void MemoryPool::ThreadCache::returnToCenterCache(void *start, size_t size, size_t bytes)
{
}
