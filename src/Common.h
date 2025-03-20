#ifndef __COMMON_H__
#define __COMMON_H__
#include <cstddef>
#include <atomic>
#include <array>
namespace MemoryPool
{
    // 对齐数和大小定义
    constexpr size_t ALIGNMENT = 8;
    // 256KB
    constexpr size_t MAX_BYTES = 256 * 1024;
    // ALIGNMENT等于void*指针的大小
    constexpr size_t FREE_LIST_SIZE = MAX_BYTES / ALIGNMENT;

    constexpr size_t PAGE_SIZE = 4096;
    /**
     * @brief 内存块头部信息
     *
     */
    struct BlockHeader
    {
        size_t size;       // 内存块大小
        bool inUse;        // 是否在使用中
        BlockHeader *next; // 指向下一个内存块
    };

    /**
     * @brief 大小类管理
     *
     */
    class SizeClass
    {
    public:
        static size_t roundUp(size_t bytes)
        {
            return (bytes + ALIGNMENT - 1) & ~(ALIGNMENT - 1);
        }

        static size_t getIndex(size_t bytes)
        {
            // bytes最小未ALIGNMENT
            bytes = std::max(bytes, ALIGNMENT);
            return (bytes + ALIGNMENT - 1) / ALIGNMENT - 1;
        }
    };
}
#endif