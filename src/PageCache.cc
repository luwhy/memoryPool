#include "PageCache.h"
#include <sys/mman.h>
#include <cstring>
namespace MemoryPool
{

    void *PageCache::allocateSpan(size_t numPages)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        // 返回第一个大于等于numpages的元素迭代器
        auto it = freeSpans_.lower_bound(numPages);
        if (it != freeSpans_.end())
        {
            Span *span = it->second;
            // 将要被取出的span取出，如果next不为空，则用next替换
            if (span->next)
            {
                freeSpans_[it->first] = span->next;
            }
            else
            {
                freeSpans_.erase(it);
            }
            // 大于所需numPages，进行分割

            if (span->numPages > numPages)
            {
                Span *newspan = new Span;
                newspan->pageAddr = static_cast<char *>(span->pageAddr) + numPages * PAGE_SIZE;
                newspan->numPages = span->numPages - numPages;
                newspan->next = nullptr;
                // 将超出的部分放回空闲Span*列表头部,像是哈希表+链表
                auto &list = freeSpans_[newspan->numPages];
                newspan->next = list;
                list = newspan;
                span->numPages = numPages;
            }
        }
        void *memory = systemAlloc(numPages);
        if (!memory)
            return nullptr;

        // 创建新的span
        Span *newSpan = new Span;
        newSpan->pageAddr = memory;
        newSpan->numPages = numPages;
        newSpan->next = nullptr;
        spanMAP_[memory] = newSpan;
        return memory;
    }

    void *PageCache::deallocateSpan(void *ptr, size_t numPages)
    {
        return nullptr;
    }

    void *PageCache::systemAlloc(size_t numPages)
    {
        size_t size = numPages * PAGE_SIZE;
        // mmap分配内存
        // mmap 分配的是进程地址空间：mmap 分配的内存位于进程的地址空间，生命周期独立于函数栈帧，函数返回后内存仍然有效。
        // 返回指针是合法的：返回的指针指向的是 mmap 分配的内存，而不是栈上的局部变量，因此不会因函数返回而失效。
        void *ptr = mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        if (ptr == MAP_FAILED)
            return nullptr;
        // 清零内存
        memset(ptr, 0, size);
        return ptr;
    }
}