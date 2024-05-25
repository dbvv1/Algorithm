#include<vector>
using namespace std;

// ???????

// ???
class IndexTree
{
private:
    vector<int> tree;

    int lowbit(int x)
    {
        return x & (-x);
    }

    int query(int n)
    {
        int ans = 0;
        for (int pos = n; pos; pos -= lowbit(pos))
            ans += tree[pos];
        return ans;
    }

public:

    IndexTree(vector<int>& nums)
    {
        tree.resize(nums.size() + 1, 0);
        for (int i = 0; i < nums.size(); i++)
        {
            update(i + 1, nums[i]);
        }
    }

    int query(int a, int b)
    {
        return query(b) - query(a - 1);
    }

    void update(int i, int x)
    {
        for (int pos = i; pos < tree.size(); pos += lowbit(pos))
            tree[pos] += x;
    }

};
// ???????????