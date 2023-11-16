#include <string>
#include <vector>
#include<initializer_list>
using namespace std;

const int mod = 1e9 + 7;
int n;
int m;


// ����������� TODO:���ϻ��� �������������
int longestCommonSubsequence1(string s1, string s2)
{
	int len1 = s1.size();
	int len2 = s2.size();
	//dp[i][j] ��ʾs1 ǰi���ַ� ��s2 ǰj���ַ� ʱ��ans
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
//�Ż� ���һά�����
int longestCommonSubsequence2(string s1, string s2)
{
	int len1 = s1.size();
	int len2 = s2.size();
	//dp[i][j] ��ʾs1 ǰi���ַ� ��s2 ǰj���ַ� ʱ��ans
	//ÿ����������ߣ��ϱߣ����Ͻ�
	vector<int> dp(len2 + 1, 0);
	for (int i = 1; i <= len1; i++)
	{
		int leftUp = dp[0]; //��¼���Ͻǵ����
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

//�༭�������� ���⣺��s1ת����s2 ���Խ�����ӣ�ɾ�����滻���ֲ���
//������ߣ��ϱߣ����Ͻ�  ͬ������Ż���һά�����
int minDistance1(string s1, string s2) 
{
	int len1 = s1.size();
	int len2 = s2.size();
	//dp[i][j] ��ʾs1 ǰi���ַ� ��s2 ǰj���ַ� ʱ��ans
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
				//����ѡ����ӣ�ɾ�����滻 ���γ��Լ���
				int p = min(dp[i][j - 1], min(dp[i - 1][j], dp[i - 1][j - 1]));
				dp[i][j] = p + 1;
			}
		}
	}
	return dp[len1][len2];
}



//�������ķ�����
//����һ�� �ݹ� + ���仯���� + ��׺���Ż�
int dp3[11][51][51];
int apples[51][51];    //post[i][j]��ʾ��i jΪ��ʼ���ľ������ж��ٸ�ƻ��

//��ǰ�ǵ�i���и�Ѿ��и�˵�x�� ��y��   ���ش�ʱ�����
int f(int i, int x, int y, vector<string>& pizze, int k)
{
	//��ֹ���� ����Ҫ�и���
	if (i == k - 1)
	{
		//���Ҫ����һ���ж� �ж�ʣ������ƻ��
		if (apples[x][y] != 0) dp3[i][x][y] = 1;
		return 	dp3[i][x][y];
	}
	if (dp3[i][x][y] != 0) return dp3[i][x][y];
	//ö��Ҫ�����и���к���   Ҫ�ж��и�ĵط��Ƿ�������һ��ƻ������׺���Ż���
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
	//��Ҫ������k-1��
	//dp[i][j][w]��ʾ
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

//�����ַ���
bool isInterleave(string s1, string s2, string s3)
{
	//dp[i][j]��ʾs1ǰi���ַ���s2ǰj���ַ� �ܷ���ϳ�s3ǰi+j���ַ�
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
			//�������һ���ַ���˭�㶨
			bool p1 = (dp[i - 1][j]) && (s1[i - 1] == s3[i + j - 1]);
			bool p2 = (dp[i][j - 1]) && (s2[j - 1] == s3[i + j - 1]);
			dp[i][j] = p1 | p2;
		}
	}

	return dp[len1][len2];

}