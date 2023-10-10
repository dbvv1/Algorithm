#include <string>
#include <vector>
using namespace std;

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
				dp[i][j] = min({ dp[i][j - 1],dp[i - 1][j],dp[i - 1][j - 1] }) + 1;
			}
		}
	}
	return dp[len1][len2];
}
