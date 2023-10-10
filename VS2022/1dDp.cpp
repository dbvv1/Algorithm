#include <vector>
using namespace std;

//�����������
int lengthOfLIS(vector<int>& nums)
{
    int n = nums.size();
    vector<int> ends(n, INT_MAX);
    int right = -1;
    for (int i = 0; i < nums.size(); i++)
    {
        //���ж��ֲ��� ���ұ�nums[i]��ĵ�һ����
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

//����������еĸ��� O��n^2�� TODO:���Ż�
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
                    cnt[i] = cnt[j]; // ���ü���
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
            ans = cnt[i]; // ���ü���
        }
        else if (dp[i] == maxLen) 
        {
            ans += cnt[i];
        }
    }
    return ans;
}