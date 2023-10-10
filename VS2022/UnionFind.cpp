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

    int find(int x) { // 查找x所在的集合，同时进行路径压缩
        if (parent[x] != x) 
        {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    int findSize(int x) { //查找x所在集合的总元素数目
        return size[find(x)];
    }

    void unionSet(int x, int y) { // 合并x和y所在的集合
        int rootX = find(x);
        int rootY = find(y);

        // 按集合的大小合并
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
    { // 判断x和y是否属于同一个集合
        return find(x) == find(y);
    }
};
