#include <cassert>
#include <new>
//手写实现 memcpy
void* memcpy(void* dest, const void* src, size_t n)
{
    char* cdest = (char*)dest;
    const char* csrc = (const char*)src;
    for (size_t i = 0; i < n; ++i)
    {
        cdest[i] = csrc[i];
    }
    return dest;
}

class MemoryPool
{
private:
    struct FreeBlock
    {
        FreeBlock* next;
    };

    void* pool; // 指向预分配内存的指针
    FreeBlock* freeList; // 空闲块链表头指针
    size_t blockSize; // 每个块的大小
    unsigned int blockCount; // 块的数量

public:
    MemoryPool(size_t blockSize, unsigned int blockCount)
        : blockSize(blockSize), blockCount(blockCount), pool(nullptr), freeList(nullptr)
    {
        assert(blockSize >= sizeof(FreeBlock*)); // 确保块大小足以存放一个指针
        size_t poolSize = blockSize * blockCount;
        pool = ::operator new(poolSize); // 使用全局operator new分配一大块内存

        // 初始化空闲块链表
        char* currentBlock = static_cast<char*>(pool);
        for (unsigned int i = 0; i < blockCount; i++)
        {
            auto* freeBlock = reinterpret_cast<FreeBlock*>(currentBlock);
            freeBlock->next = freeList;
            freeList = freeBlock;
            currentBlock += blockSize;
        }
    }

    ~MemoryPool()
    {
        ::operator delete(pool); // 释放整个内存池
    }

    void* allocate()
    {
        if (!freeList)
        {
            throw std::bad_alloc();
        }
        // 从空闲链表中移除一个块并返回
        FreeBlock* block = freeList;
        freeList = freeList->next;
        return block;
    }

    void deallocate(void* pointer)
    {
        // 将块回收到空闲链表
        auto* freeBlock = static_cast<FreeBlock*>(pointer);
        freeBlock->next = freeList;
        freeList = freeBlock;
    }
};

// 示例类
class MyClass
{
public:
    int data;

    MyClass(int val) : data(val)
    {
    }

    void* operator new(size_t size, MemoryPool& pool)
    {
        return pool.allocate();
    }

    void operator delete(void* pointer, MemoryPool& pool)
    {
        pool.deallocate(pointer);
    }
};
