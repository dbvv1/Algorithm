#include<stdexcept>
#include<vector>

//template<typename T>
//class SimpleDeque
//{
//private:
//
//    struct node
//    {
//        T* start;    //当前连续空间的首地址
//        T* cur;      //当前正在遍历的元素
//        T* end;      //当前连续空间的末尾地址
//        T** place;   //当前连续空间在中控器中的位置
//    };
//
//    T** map;         //中控器，每个元素指向一段连续的空间
//    node start;      //map中首个连续空间的信息
//    node finish;     //map中最后连续空间的信息
//
//    size_t block_size;  //每一段连续空间的大小
//    size_t size;        //当前deque中元素个数
//

//};


template<typename T, size_t BlockSize = 512>
class SimpleDeque
{
private:
    struct Block
    {
        T values[BlockSize / sizeof(T)];  //块中的元素
    };

    std::vector<Block*> blocks;                    //所有的块
    int startIdx, endIdx;                       //在第一个和最后一个块中的元素的索引

    size_t elemNumInBlock = BlockSize / sizeof(T); //每一块中元素的数目
    size_t size;                                   //元素的总数量

public:

    //构造函数 析构函数
    SimpleDeque() : startIdx(-1) , endIdx(elemNumInBlock), size(0)
    {

    }

    ~SimpleDeque()
    {
        for (Block* block : blocks)
            delete block;
    }


    //头尾插入和删除操作
    
    void push_front(const T& value)
    {
        if (startIdx == -1)
        {
            blocks.insert(blocks.begin(), new Block);
            startIdx = elemNumInBlock;
        }
        blocks.front()->values[--startIdx] = value;
        ++size;
    }

    void push_back(const T& value)
    {
        if (endIdx == elemNumInBlock)
        {
            blocks.push_back(new Block);
            endIdx = -1;
        }
        blocks.back()->values[++endIdx] = value;
        ++size;
    }

    void pop_front()
    {
        if (empty())
        {
            throw std::underflow_error("The deque is empty.");
        }
        ++startIdx;
        if (startIdx == elemNumInBlock)
        {
            delete blocks.front();
            blocks.erase(blocks.begin());
            startIdx = 0;
        }
        --size;
    }

    void pop_back()
    {
        if (empty())
        {
            throw std::underflow_error("The deque is empty.");
        }
        --endIdx;
        if (endIdx == -1)
        {
            delete blocks.back();
            blocks.pop_back();
            endIdx = elemNumInBlock;
        }
        --size;
    }

    //查找操作

    T& front() 
    {
        if (empty())
        {
            throw std::underflow_error("The deque is empty.");
        }
        return blocks.front()->values[startIdx];
    }

    T& back() 
    {
        if (empty())
        {
            throw std::underflow_error("The deque is empty.");
        }
        return blocks.back()->values[endIdx];
    }

    T& operator[](size_t index) 
    {
        if (index >= size)
        {
            throw std::out_of_range("Index out of range.");
        }
        size_t blockIndex = index / elemNumInBlock;
        size_t elemIndex = index % elemNumInBlock;
        return blocks[blockIndex]->values[elemIndex];
    }

    T& at(size_t index)
    {
        return operator[](index);
    }

    //返回大小 判空

    size_t getSize() const { return size; }

    bool empty() const { return size == 0; }
};

