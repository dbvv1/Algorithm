#include <vector>
using namespace std;

class UnionFind {
private:
    vector<int> parent;
    vector<int> size;

public:
    UnionFind(int n) {
        size.resize(n, 1);
        parent.resize(n);
        for (int i = 0; i < n; i++) 
        {
            parent[i] = i;
        }
    }

    int find(int x) { // ����x���ڵļ��ϣ�ͬʱ����·��ѹ��
        if (parent[x] != x) 
        {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    int findSize(int x) { //����x���ڼ��ϵ���Ԫ����Ŀ
        return size[find(x)];
    }

    void unionSet(int x, int y) { // �ϲ�x��y���ڵļ���
        int rootX = find(x);
        int rootY = find(y);

        // �����ϵĴ�С�ϲ�
        if (size[rootX] > size[rootY]) {
            parent[rootY] = rootX;
            size[rootX] += size[rootY];
        }
        else if (size[rootX] < size[rootY]) {
            parent[rootX] = rootY;
            size[rootY] += size[rootX];
        }
        else if (rootX != rootY) {
            parent[rootY] = rootX;
            size[rootX] += size[rootY];
        }


    }

    bool isConnected(int x, int y) 
    { // �ж�x��y�Ƿ�����ͬһ������
        return find(x) == find(y);
    }
};
