#ifndef __PAGECACHE_H__
#define __PAGECACHE_H__
#include "Common.h"
#include <map>
#include <mutex>
namespace MemoryPool
{
    class PageCache
    {
    public:
        /**
         * @brief 静态局部变量只会在第一次调用 getInstance 时被创建，并在程序的生命周期内保持存在。单例
         *
         * @return PageCache&
         */
        static PageCache &getInstance()
        {
            static PageCache instance;
            return instance;
        }
        /**
         * @brief 分配指定页数的span（一段连续的内存页）
         *
         * @param numPages
         * @return void*
         */
        void *allocateSpan(size_t numPages);

        /**
         * @brief 释放span
         *
         * @param ptr
         * @param numPages
         * @return void*
         */
        void *deallocateSpan(void *ptr, size_t numPages);

    private:
        PageCache();
        /**
         * @brief 向系统申请内存
         *
         * @param numPages
         * @return void*
         */
        void *systemAlloc(size_t numPages);

    private:
        struct Span
        {
            // 页起始地址
            void *pageAddr;
            // 页数
            size_t numPages;

            // 下一个span地址
            Span *next;
        };

        // 按页数管理空闲span，不同页数对应不同span链表
        std::map<size_t, Span *> freeSpans_;

        // 页号到span的映射，用于回收
        std::map<void *, Span *> spanMAP_;

        std::mutex mutex_;
    };
}
#endif