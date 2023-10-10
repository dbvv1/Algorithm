#include <string>
#include <vector>
using namespace std;

// 最长公共子序列 TODO:加上回溯 构造这个子序列
int longestCommonSubsequence1(string s1, string s2)
{
	int len1 = s1.size();
	int len2 = s2.size();
	//dp[i][j] 表示s1 前i个字符 和s2 前j个字符 时的ans
	vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));
	for (int i = 1; i <= len1; i++)
	{
		for (int j = 1; j <= len2; j++)
		{
			if (s1[i - 1] == s2[j - 1])
				dp[i][j] = dp[i - 1][j - 1] + 1;
			else
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
		}
	}
	return dp[len1][len2];

}
//优化 变成一维的情况
int longestCommonSubsequence2(string s1, string s2)
{
	int len1 = s1.size();
	int len2 = s2.size();
	//dp[i][j] 表示s1 前i个字符 和s2 前j个字符 时的ans
	//每个数依赖左边，上边，左上角
	vector<int> dp(len2 + 1, 0);
	for (int i = 1; i <= len1; i++)
	{
		int leftUp = dp[0]; //记录左上角的情况
		for (int j = 1; j <= len2; j++)
		{
			int t = dp[j];
			if (s1[i - 1] == s2[j - 1])
				dp[j] = leftUp + 1;
			else
				dp[j] = max(dp[j], dp[j - 1]);
			leftUp = t;
		}
	}
	return dp[len2];

}

//编辑距离问题 题意：将s1转化成s2 可以进行添加，删除，替换三种操作
//依赖左边，上边，左上角  同理可以优化成一维的情况
int minDistance1(string s1, string s2) 
{
	int len1 = s1.size();
	int len2 = s2.size();
	//dp[i][j] 表示s1 前i个字符 和s2 前j个字符 时的ans
	vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));
	for (int i = 1; i <= len1; i++) dp[i][0] = i;
	for (int j = 1; j <= len2; j++) dp[0][j] = j;
	for (int i = 1; i <= len1; i++)
	{
		for (int j = 1; j <= len2; j++)
		{
			if (s1[i - 1] == s2[j - 1])
				dp[i][j] = dp[i - 1][j - 1];
			else
			{
				//三种选择，添加，删除，替换 依次尝试即可
				dp[i][j] = min({ dp[i][j - 1],dp[i - 1][j],dp[i - 1][j - 1] }) + 1;
			}
		}
	}
	return dp[len1][len2];
}
