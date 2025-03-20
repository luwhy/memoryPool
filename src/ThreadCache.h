#ifndef __THREAD_CACHE_H__
#define __THREAD_cACHE_H__
#include <iostream>
#include <array>
#include "Common.h"
namespace MemoryPool
{

    // namespace memoryPool

    class ThreadCache
    {
    public:
        static ThreadCache *getInstance()
        {
            static thread_local ThreadCache instance;
            return &instance;
        }
        void *allocate(size_t index);

        void deallocate(void *ptr, size_t size);

    private:
        ThreadCache()
        {
            freeList_.fill(nullptr);
            freeListSize_.fill(0);
        }
        /**
         * @brief 从中心缓存获取内存
         *
         */
        void *fetchFromCenterCache(size_t index);

        void returnToCenterCache(void *start, size_t size, size_t bytes);

        bool shouldReturnToCenterCache(size_t index);

        // 每个线程的自由列表数组
        std::array<void *, FREE_LIST_SIZE> freeList_;

        // 自由链表的大小统计
        std::array<size_t, FREE_LIST_SIZE> freeListSize_;
    };
}
#endif