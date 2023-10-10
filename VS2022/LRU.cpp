#include<vector>;
#include<unordered_map>
#include<list>
#include<queue>
using namespace std;

//最近最久未使用算法
class LRUCache1 {
private:
    //规定链表 头部为新的元素 尾部为最久未使用
    list<pair<int, int>> cache;   //链表 记录 键值对  位于头部的值最后被访问， 位于尾部的值优先淘汰
    unordered_map<int, decltype(cache.begin())> hash; //哈希表 记录 键值 和 该值的迭代器
    int cap;
public:
    LRUCache1(int capacity) :cap(capacity)
    {

    }

    int get(int key)
    {
        //哈希表中没有key，则说明Cache中不存在该元素
        if (hash.find(key) == hash.end()) return -1;

        //取出该元素返回 并且 更新该元素在链表中的位置
        int value = (*hash[key]).second;
        cache.erase(hash[key]);
        cache.push_front({ key,value });
        hash[key] = cache.begin();
        return value;

    }

    void put(int key, int value)
    {
        //Cache中已经有该元素 进行替换操作
        if (hash.find(key) != hash.end())
        {
            //需要更新位置
            cache.erase(hash[key]);
            cache.push_front({ key,value });
            hash[key] = cache.begin();
        }
        //Cache中没有该元素 需要添加
        else
        {
            //Cache 中元素已满 需要进行页面置换
            if (cache.size() == cap)
            {
                hash.erase(cache.back().first);
                cache.erase(--cache.end());
                cache.push_front({ key,value });
                hash[key] = cache.begin();
            }
            //Cache 未满 直接添加
            else
            {
                cache.push_front({ key,value });
                hash[key] = cache.begin();
            }
        }
    }
};


class LRUCache2 {
    //规定链表 末尾为新的元素 头部为最久未使用
    const int cap;
    list<pair<int, int>> cache;
    unordered_map<int, decltype(cache.begin())> hash;
public:
    LRUCache2(int capacity) : cap(capacity) {}

    int get(int key) 
    {
        if (!hash.count(key))
            return -1;
        cache.splice(cache.cend(), cache, hash[key]);
        return hash[key]->second;
    }

    void put(int key, int value) 
    {
        if (!hash.count(key)) 
        {
            if (cache.size() == cap)
            {
                hash.erase(cache.front().first);
                cache.pop_front();
            }

            hash[key] = cache.emplace(cache.cend(), key, value);
        }
        else 
        {
            hash[key]->second = value;
            cache.splice(cache.cend(), cache, hash[key]);
        }
    }
};
