#include<map>
#include<unordered_map>
#include<set>
#include<list>
using namespace std;

struct Node1 {
    int cnt;          //Ƶ��
    int time;         //�����ʱ��
    int key, value;   //��ֵ��

    //�Զ������򷽷�
    bool operator< (const Node1& rhs) const
    {
        //Ƶ����ͬʱ ʱ���С(���)������ǰ��  ����Ƶ�ʸ�С������ǰ��
        return cnt == rhs.cnt ? time < rhs.time : cnt < rhs.cnt;
    }
};


//����һ�� ��ϣ�� + ����� set 
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
            //��Ҫ���м������
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

// ����Ľڵ���Ϣ
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

        // �����ǰ����Ϊ�գ�������Ҫ�ڹ�ϣ����ɾ�����Ҹ���minFreq
        if (freq_table[freq].size() == 0) 
        {
            freq_table.erase(freq);
            if (minfreq == freq) minfreq += 1;
        }
        // ���뵽 freq + 1 ��
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
            // ������������Ҫ����ɾ������
            if (key_table.size() == capacity) 
            {
                // ͨ�� minFreq �õ� freq_table[minFreq] �����ĩβ�ڵ�
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
            // �� get ��������һ�£�������Ҫ���»����ֵ
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


//��д˫������ + �򻯰汾
class Node {
public:
    int key, value, freq = 1; // ����ֻ����һ��
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
        if (it == key_to_node.end()) { // û���Ȿ��
            return nullptr;
        }
        auto node = it->second; // ���Ȿ��
        remove(node); // ���Ȿ������
        auto dummy = freq_to_dummy[node->freq];
        if (dummy->prev == dummy) { // ��������������ǿյ�
            freq_to_dummy.erase(node->freq); // �Ƴ�������
            delete dummy; // �ͷ��ڴ�
            if (min_freq == node->freq) {
                min_freq++;
            }
        }
        push_front(++node->freq, node); // �����ұ��������������
        return node;
    }

    // ����һ���µ�˫������
    Node* new_list() {
        auto dummy = new Node(); // �ڱ��ڵ�
        dummy->prev = dummy;
        dummy->next = dummy;
        return dummy;
    }

    // ������ͷ���һ���ڵ㣨��һ������������棩
    void push_front(int freq, Node* x) {
        auto it = freq_to_dummy.find(freq);
        if (it == freq_to_dummy.end()) { // �������ǿյ�
            it = freq_to_dummy.emplace(freq, new_list()).first;
        }
        auto dummy = it->second;
        x->prev = dummy;
        x->next = dummy->next;
        x->prev->next = x;
        x->next->prev = x;
    }

    // ɾ��һ���ڵ㣨���һ���飩
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
        if (node) { // ���Ȿ��
            node->value = value; // ���� value
            return;
        }
        if (key_to_node.size() == capacity) { // ��̫����
            auto dummy = freq_to_dummy[min_freq];
            auto back_node = dummy->prev; // ���������������������
            key_to_node.erase(back_node->key);
            remove(back_node); // �Ƴ�
            delete back_node; // �ͷ��ڴ�
            if (dummy->prev == dummy) { // �������ǿյ�
                freq_to_dummy.erase(min_freq); // �Ƴ�������
                delete dummy; // �ͷ��ڴ�
            }
        }
        key_to_node[key] = node = new Node(key, value); // ����
        push_front(1, node); // ���ڡ����� 1 �Ρ���������
        min_freq = 1;
    }
};