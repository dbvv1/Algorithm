#include<map>
#include<unordered_map>
#include<set>
#include<list>
using namespace std;

struct Node1 {
    int cnt;          //频率
    int time;         //进入的时间
    int key, value;   //键值对

    //自定义排序方法
    bool operator< (const Node1& rhs) const
    {
        //频率相同时 时间更小(最久)的排在前面  否则频率更小的排在前面
        return cnt == rhs.cnt ? time < rhs.time : cnt < rhs.cnt;
    }
};


//方法一： 哈希表 + 有序表 set 
class LFUCache1 {
private:
    
    set<Node1> s;
    unordered_map<int, decltype(s.begin())> hash;
    int size;
    int m_capacity;
    int curTime;
public:
    LFUCache1(int capacity) :m_capacity(capacity), size(0),curTime(0) {}

    int get(int key) 
    {
        if (!hash.count(key)) return -1;
        auto& t = hash[key];
        Node1 n = *t;
        s.erase(t);
        hash.erase(key);
        n.cnt++;
        s.insert(n);
        hash[key] = s.find(n);
        
    }

    void put(int key, int value) 
    {
        if (hash.count(key))
        {
            auto& t = hash[key];
            Node1 n = *t;
            hash.erase(key);
            n.cnt++;
            s.insert(n);
            hash[key] = s.find(n);
        }
        else
        {
            //需要进行加入操作
            if (size == m_capacity)
            {
                hash.erase((*s.begin()).key);
                s.erase(s.begin());
                Node1 n; n.cnt = 1; n.time = curTime; n.key = key; n.value = value;
                s.insert(n);
                hash[key] = s.find(n);
            }
            else
            {
                Node1 n; n.cnt = 1; n.time = curTime; n.key = key; n.value = value;
                ++size;
                s.insert(n);
                hash[key] = s.find(n);
            }
        }
    }
};

// 缓存的节点信息
struct Node2 
{
    int key, val, freq;
    Node2(int _key, int _val, int _freq) : key(_key), val(_val), freq(_freq) {}
};

class LFUCache2 
{
    int minfreq, capacity;
    unordered_map<int, list<Node2>::iterator> key_table;
    unordered_map<int, list<Node2>> freq_table;

public:
    LFUCache2(int _capacity) 
    {
        minfreq = 0;
        capacity = _capacity;
        key_table.clear();
        freq_table.clear();
    }

    int get(int key) 
    {
        if (capacity == 0) return -1;
        auto it = key_table.find(key);
        if (it == key_table.end()) return -1;

        list<Node2>::iterator node = it->second;
        int val = node->val, freq = node->freq;
        freq_table[freq].erase(node);

        // 如果当前链表为空，我们需要在哈希表中删除，且更新minFreq
        if (freq_table[freq].size() == 0) 
        {
            freq_table.erase(freq);
            if (minfreq == freq) minfreq += 1;
        }
        // 插入到 freq + 1 中
        freq_table[freq + 1].push_front(Node2(key, val, freq + 1));
        key_table[key] = freq_table[freq + 1].begin();
        return val;
    }

    void put(int key, int value) 
    {
        if (capacity == 0) return;
        auto it = key_table.find(key);
        if (it == key_table.end()) 
        {
            // 缓存已满，需要进行删除操作
            if (key_table.size() == capacity) 
            {
                // 通过 minFreq 拿到 freq_table[minFreq] 链表的末尾节点
                auto it2 = freq_table[minfreq].back();
                key_table.erase(it2.key);
                freq_table[minfreq].pop_back();

                if (freq_table[minfreq].size() == 0) 
                {
                    freq_table.erase(minfreq);
                }
            }
            freq_table[1].push_front(Node2(key, value, 1));
            key_table[key] = freq_table[1].begin();
            minfreq = 1;
        }
        else 
        {
            // 与 get 操作基本一致，除了需要更新缓存的值
            list<Node2>::iterator node = it->second;
            int freq = node->freq;
            freq_table[freq].erase(node);
            if (freq_table[freq].size() == 0) 
            {
                freq_table.erase(freq);
                if (minfreq == freq) minfreq += 1;
            }
            freq_table[freq + 1].push_front(Node2(key, value, freq + 1));
            key_table[key] = freq_table[freq + 1].begin();
        }
    }
};


//手写双向链表 + 简化版本
class Node {
public:
    int key, value, freq = 1; // 新书只读了一次
    Node* prev, * next;

    Node(int k = 0, int v = 0) : key(k), value(v) {}
};

class LFUCache {
private:
    int min_freq;
    int capacity;
    unordered_map<int, Node*> key_to_node;
    unordered_map<int, Node*> freq_to_dummy;

    Node* get_node(int key) {
        auto it = key_to_node.find(key);
        if (it == key_to_node.end()) { // 没有这本书
            return nullptr;
        }
        auto node = it->second; // 有这本书
        remove(node); // 把这本书抽出来
        auto dummy = freq_to_dummy[node->freq];
        if (dummy->prev == dummy) { // 抽出来后，这摞书是空的
            freq_to_dummy.erase(node->freq); // 移除空链表
            delete dummy; // 释放内存
            if (min_freq == node->freq) {
                min_freq++;
            }
        }
        push_front(++node->freq, node); // 放在右边这摞书的最上面
        return node;
    }

    // 创建一个新的双向链表
    Node* new_list() {
        auto dummy = new Node(); // 哨兵节点
        dummy->prev = dummy;
        dummy->next = dummy;
        return dummy;
    }

    // 在链表头添加一个节点（把一本书放在最上面）
    void push_front(int freq, Node* x) {
        auto it = freq_to_dummy.find(freq);
        if (it == freq_to_dummy.end()) { // 这摞书是空的
            it = freq_to_dummy.emplace(freq, new_list()).first;
        }
        auto dummy = it->second;
        x->prev = dummy;
        x->next = dummy->next;
        x->prev->next = x;
        x->next->prev = x;
    }

    // 删除一个节点（抽出一本书）
    void remove(Node* x) {
        x->prev->next = x->next;
        x->next->prev = x->prev;
    }

public:
    LFUCache(int capacity) : capacity(capacity) {}

    int get(int key) {
        auto node = get_node(key);
        return node ? node->value : -1;
    }

    void put(int key, int value) {
        auto node = get_node(key);
        if (node) { // 有这本书
            node->value = value; // 更新 value
            return;
        }
        if (key_to_node.size() == capacity) { // 书太多了
            auto dummy = freq_to_dummy[min_freq];
            auto back_node = dummy->prev; // 最左边那摞书的最下面的书
            key_to_node.erase(back_node->key);
            remove(back_node); // 移除
            delete back_node; // 释放内存
            if (dummy->prev == dummy) { // 这摞书是空的
                freq_to_dummy.erase(min_freq); // 移除空链表
                delete dummy; // 释放内存
            }
        }
        key_to_node[key] = node = new Node(key, value); // 新书
        push_front(1, node); // 放在「看过 1 次」的最上面
        min_freq = 1;
    }
};