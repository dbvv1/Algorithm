#include<map>
#include<list>
using namespace std;

struct Node {
    int cnt;          //Ƶ��
    int time;         //
    int key, value;   //��ֵ��

    //�Զ������򷽷�
    bool operator< (const Node& rhs) const
    {
        //Ƶ����ͬʱ ʱ���С(���)������ǰ��  ����Ƶ�ʸ�С������ǰ��
        return cnt == rhs.cnt ? time < rhs.time : cnt < rhs.cnt;
    }
};


//����һ�� ��ϣ�� + ����� set
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