#include<stdexcept>
#include<vector>

//template<typename T>
//class SimpleDeque
//{
//private:
//
//    struct node
//    {
//        T* start;    //��ǰ�����ռ���׵�ַ
//        T* cur;      //��ǰ���ڱ�����Ԫ��
//        T* end;      //��ǰ�����ռ��ĩβ��ַ
//        T** place;   //��ǰ�����ռ����п����е�λ��
//    };
//
//    T** map;         //�п�����ÿ��Ԫ��ָ��һ�������Ŀռ�
//    node start;      //map���׸������ռ����Ϣ
//    node finish;     //map����������ռ����Ϣ
//
//    size_t block_size;  //ÿһ�������ռ�Ĵ�С
//    size_t size;        //��ǰdeque��Ԫ�ظ���
//

//};


template<typename T, size_t BlockSize = 512>
class SimpleDeque
{
private:
    struct Block
    {
        T values[BlockSize / sizeof(T)];  //���е�Ԫ��
    };

    std::vector<Block*> blocks;                    //���еĿ�
    int startIdx, endIdx;                       //�ڵ�һ�������һ�����е�Ԫ�ص�����

    size_t elemNumInBlock = BlockSize / sizeof(T); //ÿһ����Ԫ�ص���Ŀ
    size_t size;                                   //Ԫ�ص�������

public:

    //���캯�� ��������
    SimpleDeque() : startIdx(-1) , endIdx(elemNumInBlock), size(0)
    {

    }

    ~SimpleDeque()
    {
        for (Block* block : blocks)
            delete block;
    }


    //ͷβ�����ɾ������
    
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

    //���Ҳ���

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

    //���ش�С �п�

    size_t getSize() const { return size; }

    bool empty() const { return size == 0; }
};

