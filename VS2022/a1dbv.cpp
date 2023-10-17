#include <bits/stdc++.h>
using namespace std;

//一副牌 能否全部由顺子打完
//方法一：暴力递归

int main()
{
    string a;
    string g;

}


//第366场周赛

//第115场双周赛

//第367场周赛： 分值分布 3 4 5 5 快速冲

vector<int> findIndices(vector<int>& nums, int indexDifference, int valueDifference)
{
    //O（n）解决
    //再枚举j的同时 维护最大值和最小值即可

    int n = nums.size();
    if (indexDifference >= n) return { -1,1 };
    //从0开始枚举j
    //初始的范围为 indexDifference-n
    int mins = indexDifference;
    int maxs = indexDifference;
    for (int i = indexDifference + 1; i < n; i++)
    {
        if (nums[i] > nums[maxs]) maxs = i;
        if (nums[i] < nums[mins]) mins = i;
    }
    for (int j = 0; j < n; j++)
    {
        if (nums[j] - nums[mins] >= valueDifference) return { j,mins };
        if (nums[maxs] - nums[j] <= valueDifference) return { j,maxs };
        //我们可以不用管右边失去的，只要管
    }

}

vector<int> findIndices(vector<int>& nums, int indexDifference, int valueDifference) {
    int max_idx = 0, min_idx = 0;
    for (int j = indexDifference; j < nums.size(); j++) {
        int i = j - indexDifference;
        if (nums[i] > nums[max_idx]) {
            max_idx = i;
        }
        else if (nums[i] < nums[min_idx]) {
            min_idx = i;
        }
        if (nums[max_idx] - nums[j] >= valueDifference) {
            return { max_idx, j };
        }
        if (nums[j] - nums[min_idx] >= valueDifference) {
            return { min_idx, j };
        }
    }
    return { -1, -1 };
}



vector<vector<int>> constructProductMatrix(vector<vector<int>>& grid) 
{
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<int>> ans(n, vector<int>(m, 1));
    //想象成一维维的情况即可
    //[1,2][3,4]
    int left = grid[0][0]; int right = grid[n - 1][m - 1];
    left %= 12345; right %= 12345;
    for (int i = 1; i < n * m - 1; i++)
    {
        int x1 = i / m; int y1 = i % m;
        int x2 = (n * m - i-1) / m; int y2 = (n * m - i-1) % m;
        ans[x1][y1] *= left; ans[x1][y1] %= 12345;
        ans[x2][y2] *= right; ans[x2][y2] %= 12345;
        left *= grid[x1][y1]%12345; left %= 12345;
        right *= grid[x2][y2]%12345; right %= 12345;
    }
    ans[0][0] = right;
    ans[n - 1][m - 1] = left;

    return ans;

}