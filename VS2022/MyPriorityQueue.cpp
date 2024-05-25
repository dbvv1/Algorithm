#include <unordered_map>
#include<vector>
using namespace std;

//实现堆
template <typename T, typename Compare = std::less<T>>
class MyPriorityQueue
{
private:
    vector<T> arr;
    Compare comp;
    //总体调整堆(即从非叶子结点开始向下调整)
    void Heapify()
    {
        for (int i = (arr.size() - 2) / 2; i >= 0; i--)
        {
            PushDown(i);
        }
    }

    //从x位置开始向下调整
    void PushDown(int x)
    {
        int cur = x;
        while (cur * 2 + 1 < arr.size())
        {
            int left = cur * 2 + 1;
            int right = cur * 2 + 2;
            int choose = right == arr.size() ? left : (comp(arr[left], arr[right]) ? right : left);
            if (!comp(arr[cur], arr[choose])) break;
            swap(arr[cur], arr[choose]);
            cur = choose;
        }
    }

    //向x位置开始向上调整
    void PushUp(int x)
    {
        int cur = x;
        while ((cur - 1) / 2 >= 0)
        {
            int father = (cur - 1) / 2;
            if (comp(arr[cur], arr[father])) break;
            swap(arr[cur], arr[father]);
            cur = father;
        }
    }

public:
    MyPriorityQueue()
    {
    }

    MyPriorityQueue(const vector<int>& a) : arr(a)
    {
        Heapify();
    }

    //返回堆顶元素
    T Top()
    {
        if (arr.size() == 0) return INT_MIN;
        return arr[0];
    }

    //删除堆顶元素 并返回
    T Pop()
    {
        //将首元素与尾元素交换 并执行PushDown方法
        T res = arr[0];
        swap(arr[0], arr[arr.size() - 1]);
        arr.pop_back();
        PushDown(0);
        return res;
    }

    //往堆中添加元素x
    void Push(int x)
    {
        //在arr末尾添加元素 并且执行PushUp方法
        arr.push_back(x);
        PushUp(arr.size() - 1);
    }

    //返回堆的大小
    int Size()
    {
        return arr.size();
    }

    bool Empty()
    {
        return arr.empty();
    }
};


//在堆的基础上实现加强堆： 添加一个哈希表  <T*, int> indexMap 记录每个具体的元素的下标位置
//在向上或向下调整 进行交换时：不仅vector中值要交换，哈希表中的值也要交换
template <typename T, typename Compare = std::less<T>>
class EnhancedPriorityQueue
{
private:
    std::vector<T> arr; // 存储堆元素
    Compare comp; // 比较函数对象，用于元素比较
    std::unordered_map<T, int> position; // 哈希表，记录每个元素在堆中的位置

    // 调整堆结构以维护堆属性（从非叶子节点向下调整）
    void Heapify()
    {
        for (int i = (arr.size() - 2) / 2; i >= 0; i--)
        {
            PushDown(i);
        }
    }

    // 从位置 x 开始向下调整以保持最大堆或最小堆属性
    void PushDown(int x)
    {
        int cur = x;
        while (cur * 2 + 1 < arr.size())
        {
            int left = cur * 2 + 1;
            int right = cur * 2 + 2;
            int choose = right < arr.size() && comp(arr[left], arr[right]) ? right : left;
            if (!comp(arr[cur], arr[choose])) break;
            std::swap(arr[cur], arr[choose]);
            std::swap(position[arr[cur]], position[arr[choose]]);
            cur = choose;
        }
    }

    // 从位置 x 开始向上调整以保持最大堆或最小堆属性
    void PushUp(int x)
    {
        int cur = x;
        while (cur > 0)
        {
            int father = (cur - 1) / 2;
            if (!comp(arr[father], arr[cur])) break;
            std::swap(arr[cur], arr[father]);
            std::swap(position[arr[cur]], position[arr[father]]);
            cur = father;
        }
    }

public:
    EnhancedPriorityQueue()
    {
    }

    EnhancedPriorityQueue(const std::vector<T>& a)
    {
        // 建立堆结构
        Heapify();
        // 初始化哈希表，记录每个元素的位置
        for (int i = 0; i < arr.size(); ++i)
        {
            position[arr[i]] = i;
        }
    }

    // 返回堆顶元素，即最小或最大元素
    T Top()
    {
        if (arr.empty()) return T(); // 如果堆为空，则返回默认值
        return arr[0];
    }

    // 移除并返回堆顶元素
    T Pop()
    {
        if (arr.empty()) return T(); // 如果堆为空，则返回默认值
        T res = arr[0];
        std::swap(arr[0], arr[arr.size() - 1]);
        std::swap(position[arr[0]], position[arr[arr.size() - 1]]);
        position.erase(arr.back());
        arr.pop_back();
        if (!arr.empty()) PushDown(0);
        return res;
    }

    // 向堆中添加新元素
    void Push(const T& x)
    {
        arr.push_back(x);
        position[x] = arr.size() - 1;
        PushUp(arr.size() - 1);
    }

    // 通过元素值直接删除元素
    void Remove(const T& x)
    {
        int index = position[x];
        std::swap(arr[index], arr[arr.size() - 1]);
        std::swap(position[arr[index]], position[arr[arr.size() - 1]]);
        position.erase(arr.back());
        arr.pop_back();
        if (index < arr.size())
        {
            PushDown(index);
            PushUp(index);
        }
    }

    // 修改下标X位置的值为val
    void Modify(int x, const T& val)
    {
        if (x < 0 || x >= arr.size()) return;

        T old_val = arr[x];
        arr[x] = val;
        position.erase(old_val);
        position[val] = x;

        // 判断是向下 还是 向上调整
        if (comp(old_val, val))
        {
            PushUp(x);
        }
        else
        {
            PushDown(x);
        }
    }

    // 返回堆中元素的数量
    int Size()
    {
        return arr.size();
    }

    // 检查堆是否为空
    bool Empty()
    {
        return arr.empty();
    }
};
