#include<vector>
#include <stack>
using namespace std;



//题目一：最大正方形 (动态规划即可)
int maximalSquare(vector<vector<char>>& matrix) 
{
	//找到只包含1的最大正方形 返回面积
	//dp[i][j]表示以i j 位置作为结尾时的答案
	//则dp[i][j]=min 三个方向+1
	int n = matrix.size();
	int m = matrix[0].size();
	vector<vector<int>> dp(n, vector(m, 0));
	int ans = 0;
	for (int j = 0; j < m; j++) if (matrix[0][j] == '1') { dp[0][j] = 1; ans = 1; }
	else dp[0][j] = 0;
	for (int i = 0; i < n; i++) if (matrix[i][0] == '1') { dp[i][0] = 1; ans = 1; }
	else dp[i][0] = 0;
	for (int i = 1; i < n; i++)
	{
		for (int j = 1; j < m; j++)
		{
			if (matrix[i][j] == '0') dp[i][j] = 0;
			else
				dp[i][j] = min({ dp[i - 1][j - 1],dp[i - 1][j],dp[i][j - 1] }) + 1;

			ans = max(ans, dp[i][j]);
		}
	}
	return ans * ans;

}

//题目二：最大矩形（暴力法+单调栈优化）

//解法一：暴力枚举右下角点，并且不断往上进行扩充
int leftCount[201][201];

int maximalRectangle1(vector<vector<char>>& matrix)
{

	//方法一：预处理每个数的左边多少个连续的1  暴力枚举每个数作为右下角的情况
	int n = matrix.size();
	int m = matrix[0].size();
	for (int i = 0; i < n; i++) leftCount[i][0] = matrix[i][0] == '1' ? 1 : 0;
	for (int i = 0; i < n; i++)
		for (int j = 1; j < m; j++)
			leftCount[i][j] = matrix[i][j] == '1' ? leftCount[i][j - 1] + 1 : 0;

	int ans = 0;
	//暴力枚举每个数
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			int leftMin = leftCount[i][j];
			for (int k = i; k >= 0; k--)
			{
				leftMin = min(leftMin, leftCount[k][j]);
				ans = max(ans, leftMin * (i - k + 1));
			}
		}
	}

	return ans;

}

//方法二：使用单调栈（实际上就是柱状图中最大矩形算法）
int maximalRectangle2(vector<vector<char>>& matrix)
{
	//将martix想象成多行的柱状图
	//leftCount[i][j]表示i j 位置以及其左方一共有多少个1
	int n = matrix.size();
	int m = matrix[0].size();
	vector<vector<int>> upCount(n, vector<int>(m, 0));
	for (int j = 0; j < m; j++) upCount[0][j] = matrix[0][j] == '1' ? 1 : 0;
	for (int i = 1; i < n; i++)
		for (int j = 0; j < m; j++)
			upCount[i][j] = matrix[i][j] == '1' ? upCount[i - 1][j] + 1 : 0;
	int ans = 0;
	for (int i = 0; i < n; i++)
	{
		ans = max(ans, largestRectangleArea3(upCount[i]));
	}
	return ans;
}

//题目三：柱状图中最大矩形
//方法一：枚举以每个数作为基准值同时往两边进行扩充 
int largestRectangleArea1(vector<int>& heights) 
{
	int n = heights.size();
	vector<int> left(n, -1);		//记录每个数左边比自己小的最近数数
	vector<int> right(n, n);		//记录每个数右边比自己小的最近的数
	stack<int> s;

	//维护一个小->大的单调栈  元素进栈时进行计算
	for (int i = 0; i < n; i++)
	{
		while (!s.empty() && heights[i] <= heights[s.top()])  s.pop();
		if (!s.empty()) left[i] = s.top();
		s.push(i);
	}
	while (!s.empty()) s.pop();
	for (int i = n - 1; i >= 0; i--)
	{
		while (!s.empty() && heights[i] <= heights[s.top()]) s.pop();
		if (!s.empty()) right[i] = s.top();
		s.push(i);
	}
	int ans = 0;
	for (int i = 0; i < n; i++)
	{
		ans = max(ans, (right[i] - left[i] - 1) * heights[i]);
	}
	return ans;

}

//方法二：常数优化 两个for循环优化成一个
int largestRectangleArea2(vector<int>& heights)
{
	int n = heights.size();
	vector<int> left(n, -1);		//记录每个数左边比自己小的最近数数
	vector<int> right(n, n);		//记录每个数右边比自己小的最近的数
	stack<int> s;

	//维护一个小->大的单调栈  元素进栈时进行计算left  元素出栈时计算right
	for (int i = 0; i < n; i++)
	{
		while (!s.empty() && heights[i] <= heights[s.top()])
		{
			right[s.top()] = i;
			s.pop();
		}
		if (!s.empty()) left[i] = s.top();
		s.push(i);
	}
	int ans = 0;
	for (int i = 0; i < n; i++)
	{
		ans = max(ans, (right[i] - left[i] - 1) * heights[i]);
	}
	return ans;

}

//方法三：不使用数组 在单调栈进行的同时计算更新答案
int largestRectangleArea3(vector<int>& heights)
{
	stack<int> st;
	heights.insert(heights.begin(), 0); // 数组头部加入元素0
	heights.push_back(0); // 数组尾部加入元素0
	st.push(0);
	int result = 0;
	//核心：在栈中的数据被弹出来的时候  它的右边最近小值和左边最近小值都是可以确定的
	//细节：相同元素不弹出 前提：首位加入0
	for (int i = 1; i < heights.size(); i++)
	{
		while (heights[i] < heights[st.top()])
		{
			int mid = st.top();
			st.pop();
			int w = i - st.top() - 1;
			int h = heights[mid];
			result = max(result, w * h);
		}
		st.push(i);
	}
	return result;

}