#include <string>
#include <vector>
using namespace std;

//01����
int Bag(vector<int>& nums, int amount)
{
    //ÿ��Ӳ�ҵ�������Ϊ�����޵�
    //����ƴ�ճ��ܽ�����������Ӳ�Ҹ���
    int n = nums.size();
    vector<int> dp(amount + 1); for (int i = 0; i <= amount; i++) dp[i] = INT_MAX;
    for (int k = 0; k * nums[0] <= amount; k++) dp[k * nums[0]] = k;

    for (int i = 1; i < n; i++)
    {
        for (int j = nums[i]; j <= amount; j++)
        {
            if (dp[j - nums[i]] != INT_MAX)
                dp[j] = min(dp[j], dp[j - nums[i]] + 1);

        }
    }
    return dp[amount] == INT_MAX ? -1 : dp[amount];

}


//��ȫ����
int coinChange(vector<int>& coins, int amount)
{
    //ÿ��Ӳ�ҵ�������Ϊ�����޵�
    //����ƴ�ճ��ܽ�����������Ӳ�Ҹ���
    int n = coins.size();
    vector<int> dp(amount + 1); for (int i = 0; i <= amount; i++) dp[i] = INT_MAX;
    for (int k = 0; k * coins[0] <= amount; k++) dp[k * coins[0]] = k;

    for (int i = 1; i < n; i++)
    {
        for (int j = coins[i]; j <= amount; j++)
        {
            if (dp[j - coins[i]] != INT_MAX)
                dp[j] = min(dp[j], dp[j - coins[i]] + 1);

        }
    }
    return dp[amount] == INT_MAX ? -1 : dp[amount];

}