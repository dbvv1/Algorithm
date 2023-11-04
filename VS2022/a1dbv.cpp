#include <bits/stdc++.h>
using namespace std;

//一副牌 能否全部由顺子打完
//方法一：暴力递归

int main()
{
	char* p = new char[3]; p[0] = 'A'; p[1] = 'B'; p[2] = 'C';
	*p = 'a';
	*(p + 1) = 'b';
	*(p + 2) = '\0';
	printf("p = %s", p);
}


//最大矩形（只包含1的最大矩形） 返回矩形的面积
int leftCount[201][201];
int upCount[201][201];

int maximalRectangle(vector<vector<char>>& matrix)
{
	//如果是最大正方形则直接 以i j 位置结尾做dp
	//最大矩形不是最大正方形

	//方法一：预处理每个数的左边 上边有多少个连续的1  暴力枚举每个数作为右下角的情况
	int n = matrix.size();
	int m = matrix[0].size();
	for (int i = 0; i < n; i++) leftCount[i][0] = matrix[i][0] == '1' ? 1 : 0;
	for (int j = 0; j < m; j++) upCount[0][j] = matrix[0][j] == '1' ? 1 : 0;
	for (int i = 1; i < n; i++)
	{
		for (int j = 1; j < m; j++)
	    {
			leftCount[i][j] = matrix[i][j] == '1' ? leftCount[i][j - 1] + 1 : 0;
			upCount[i][j] = matrix[i][j] == '1' ? upCount[i - 1][j] + 1 : 0;
		}
	}

	int ans = 0;
	//暴力枚举每个数
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			int leftMin = leftCount[i][j];
			int upMin = upCount[i][j];
			ans = max(ans, max(leftMin, upMin));
			for (int k = 0; i - k >= 0 && j - k >= 0; k++)
			{
				leftMin = min(leftMin, leftCount[i - k][j - k]);
				ans = max(ans, leftMin * (k + 1));
				upMin = min(upMin, upCount[i - k][j - k]);
				ans = max(ans, upMin * (k + 1));

			}
		}
	}

	return ans;
	


}