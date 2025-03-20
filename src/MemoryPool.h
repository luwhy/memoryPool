#ifndef __MEMORY_POOL_H__
#define __MEMORY_POOL_H__
#include "ThreadCache.h"
namespace MemoryPool
{
    class MemoryPool
    {
    public:
        static void *allocate(size_t size)
        {
            return ThreadCache::getInstance()->allocate(size);
        }
        static void deallocate(void *ptr, size_t size)
        {
            return ThreadCache::getInstance()->deallocate(ptr, size);
        }
    };
}
#endif