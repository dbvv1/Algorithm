#include <cassert>
#include <new>
//��дʵ�� memcpy
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

    void* pool; // ָ��Ԥ�����ڴ��ָ��
    FreeBlock* freeList; // ���п�����ͷָ��
    size_t blockSize; // ÿ����Ĵ�С
    unsigned int blockCount; // �������

public:
    MemoryPool(size_t blockSize, unsigned int blockCount)
        : blockSize(blockSize), blockCount(blockCount), pool(nullptr), freeList(nullptr)
    {
        assert(blockSize >= sizeof(FreeBlock*)); // ȷ�����С���Դ��һ��ָ��
        size_t poolSize = blockSize * blockCount;
        pool = ::operator new(poolSize); // ʹ��ȫ��operator new����һ����ڴ�

        // ��ʼ�����п�����
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
        ::operator delete(pool); // �ͷ������ڴ��
    }

    void* allocate()
    {
        if (!freeList)
        {
            throw std::bad_alloc();
        }
        // �ӿ����������Ƴ�һ���鲢����
        FreeBlock* block = freeList;
        freeList = freeList->next;
        return block;
    }

    void deallocate(void* pointer)
    {
        // ������յ���������
        auto* freeBlock = static_cast<FreeBlock*>(pointer);
        freeBlock->next = freeList;
        freeList = freeBlock;
    }
};

// ʾ����
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
