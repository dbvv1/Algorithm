#include <string>
#include <vector>
#include<initializer_list>
using namespace std;

const int mod = 1e9 + 7;
int n;
int m;


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
				int p = min(dp[i][j - 1], min(dp[i - 1][j], dp[i - 1][j - 1]));
				dp[i][j] = p + 1;
			}
		}
	}
	return dp[len1][len2];
}



//切披萨的方案数
//方法一： 递归 + 记忆化搜索 + 后缀和优化
int dp3[11][51][51];
int apples[51][51];    //post[i][j]表示以i j为初始起点的矩形中有多少个苹果

//当前是第i次切割，已经切割到了第x行 第y列   返回此时的情况
int f(int i, int x, int y, vector<string>& pizze, int k)
{
	//终止条件 不需要切割了
	if (i == k - 1)
	{
		//最后还要进行一次判断 判断剩下有无苹果
		if (apples[x][y] != 0) dp3[i][x][y] = 1;
		return 	dp3[i][x][y];
	}
	if (dp3[i][x][y] != 0) return dp3[i][x][y];
	//枚举要进行切割的行和列   要判断切割的地方是否至少有一个苹果（后缀和优化）
	int sum = 0;
	bool have = false;
	for (int row = x; row < n; row++)
	{
		if (apples[row][y] - apples[row + 1][y] > 0) have = true;
		if (have)
		{
			sum += f(i + 1, row + 1, y, pizze, k);
			sum %= mod;
		}

	}
	have = false;
	for (int col = y; col < m; col++)
	{
		if (apples[x][col] - apples[x][col + 1] > 0) have = true;
		if (have)
		{
			sum += f(i + 1, x, col + 1, pizze, k);
			sum %= mod;
		}
	}
	dp3[i][x][y] = sum;
	return sum;
}


int ways(vector<string>& pizza, int k)
{	
	//需要切披萨k-1次
	//dp[i][j][w]表示
	n = pizza.size();
	m = pizza[0].size();
	apples[n - 1][m - 1] = pizza[n - 1][m - 1] == 'A';
	for (int i = n - 1; i >= 0; i--)
	{
		for (int j = m - 1; j >= 0; j--)
		{
			apples[i][j] = apples[i + 1][j] + apples[i][j + 1] - apples[i + 1][j + 1];
			if (pizza[i][j] == 'A') apples[i][j]++;
		}
	}
	return f(0, 0, 0, pizza, k);
}

//交错字符串
bool isInterleave(string s1, string s2, string s3)
{
	//dp[i][j]表示s1前i个字符和s2前j个字符 能否组合成s3前i+j个字符
	int len1 = s1.size();
	int len2 = s2.size();
	if (len1 + len2 != s3.size()) return false;
	bool dp[len1 + 1][len2 + 1]; dp[len1][len2] = false;
	dp[0][0] = true;
	for (int j = 1; j <= len2; j++)
	{
		if (s2[j - 1] != s3[j - 1]) break;
		dp[0][j] = true;
	}
	for (int i = 1; i < len1; i++)
	{
		if (s1[i - 1] != s3[i - 1]) break;
		dp[i][0] = true;
	}

	for (int i = 1; i <= len1; i++)
	{
		for (int j = 1; j <= len2; j++)
		{
			//根据最后一个字符由谁搞定
			bool p1 = (dp[i - 1][j]) && (s1[i - 1] == s3[i + j - 1]);
			bool p2 = (dp[i][j - 1]) && (s2[j - 1] == s3[i + j - 1]);
			dp[i][j] = p1 | p2;
		}
	}

	return dp[len1][len2];

}