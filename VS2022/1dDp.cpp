#include <vector>
using namespace std;

//最长递增子序列
int lengthOfLIS(vector<int>& nums)
{
    int n = nums.size();
    vector<int> ends(n, INT_MAX);
    int right = -1;
    for (int i = 0; i < nums.size(); i++)
    {
        //进行二分查找 查找比nums[i]大的第一个数
        int l = 0, r = right;
        int target = right + 1;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (ends[mid] >= nums[i])
            {
                target = mid;
                r = mid - 1;
            }
            else
                l = mid + 1;
        }
        if (target == right + 1)
            right++;
        ends[target] = nums[i];
    }
    return right + 1;
}

//最长递增子序列的个数 O（n^2） TODO:有优化
int findNumberOfLIS(vector<int>& nums) 
{
    int n = nums.size(), maxLen = 0, ans = 0;
    vector<int> dp(n), cnt(n);
    for (int i = 0; i < n; ++i)
    {
        dp[i] = 1;
        cnt[i] = 1;
        for (int j = 0; j < i; ++j) 
        {
            if (nums[i] > nums[j]) 
            {
                if (dp[j] + 1 > dp[i]) 
                {
                    dp[i] = dp[j] + 1;
                    cnt[i] = cnt[j]; // 重置计数
                }
                else if (dp[j] + 1 == dp[i]) 
                {
                    cnt[i] += cnt[j];
                }
            }
        }
        if (dp[i] > maxLen) 
        {
            maxLen = dp[i];
            ans = cnt[i]; // 重置计数
        }
        else if (dp[i] == maxLen) 
        {
            ans += cnt[i];
        }
    }
    return ans;
}