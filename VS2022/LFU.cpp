#include<map>
#include<list>
using namespace std;

struct Node {
    int cnt;          //频率
    int time;         //
    int key, value;   //键值对

    //自定义排序方法
    bool operator< (const Node& rhs) const
    {
        //频率相同时 时间更小(最久)的排在前面  否则频率更小的排在前面
        return cnt == rhs.cnt ? time < rhs.time : cnt < rhs.cnt;
    }
};


//方法一： 哈希表 + 有序表 set
class LFUCache {
private:


public:
    LFUCache(int capacity) {

    }

    int get(int key) {

    }

    void put(int key, int value) {

    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */