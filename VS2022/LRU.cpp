#include<vector>;
#include<unordered_map>
#include<list>
#include<queue>
using namespace std;

//������δʹ���㷨
class LRUCache1 {
private:
    //�涨���� ͷ��Ϊ�µ�Ԫ�� β��Ϊ���δʹ��
    list<pair<int, int>> cache;   //���� ��¼ ��ֵ��  λ��ͷ����ֵ��󱻷��ʣ� λ��β����ֵ������̭
    unordered_map<int, decltype(cache.begin())> hash; //��ϣ�� ��¼ ��ֵ �� ��ֵ�ĵ�����
    int cap;
public:
    LRUCache1(int capacity) :cap(capacity)
    {

    }

    int get(int key)
    {
        //��ϣ����û��key����˵��Cache�в����ڸ�Ԫ��
        if (hash.find(key) == hash.end()) return -1;

        //ȡ����Ԫ�ط��� ���� ���¸�Ԫ���������е�λ��
        int value = (*hash[key]).second;
        cache.erase(hash[key]);
        cache.push_front({ key,value });
        hash[key] = cache.begin();
        return value;

    }

    void put(int key, int value)
    {
        //Cache���Ѿ��и�Ԫ�� �����滻����
        if (hash.find(key) != hash.end())
        {
            //��Ҫ����λ��
            cache.erase(hash[key]);
            cache.push_front({ key,value });
            hash[key] = cache.begin();
        }
        //Cache��û�и�Ԫ�� ��Ҫ���
        else
        {
            //Cache ��Ԫ������ ��Ҫ����ҳ���û�
            if (cache.size() == cap)
            {
                hash.erase(cache.back().first);
                cache.erase(--cache.end());
                cache.push_front({ key,value });
                hash[key] = cache.begin();
            }
            //Cache δ�� ֱ�����
            else
            {
                cache.push_front({ key,value });
                hash[key] = cache.begin();
            }
        }
    }
};


class LRUCache2 {
    //�涨���� ĩβΪ�µ�Ԫ�� ͷ��Ϊ���δʹ��
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
