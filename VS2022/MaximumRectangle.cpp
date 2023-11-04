#include<vector>
#include <stack>
using namespace std;



//��Ŀһ����������� (��̬�滮����)
int maximalSquare(vector<vector<char>>& matrix) 
{
	//�ҵ�ֻ����1����������� �������
	//dp[i][j]��ʾ��i j λ����Ϊ��βʱ�Ĵ�
	//��dp[i][j]=min ��������+1
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

//��Ŀ���������Σ�������+����ջ�Ż���

//�ⷨһ������ö�����½ǵ㣬���Ҳ������Ͻ�������
int leftCount[201][201];

int maximalRectangle1(vector<vector<char>>& matrix)
{

	//����һ��Ԥ����ÿ��������߶��ٸ�������1  ����ö��ÿ������Ϊ���½ǵ����
	int n = matrix.size();
	int m = matrix[0].size();
	for (int i = 0; i < n; i++) leftCount[i][0] = matrix[i][0] == '1' ? 1 : 0;
	for (int i = 0; i < n; i++)
		for (int j = 1; j < m; j++)
			leftCount[i][j] = matrix[i][j] == '1' ? leftCount[i][j - 1] + 1 : 0;

	int ans = 0;
	//����ö��ÿ����
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

//��������ʹ�õ���ջ��ʵ���Ͼ�����״ͼ���������㷨��
int maximalRectangle2(vector<vector<char>>& matrix)
{
	//��martix����ɶ��е���״ͼ
	//leftCount[i][j]��ʾi j λ���Լ�����һ���ж��ٸ�1
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

//��Ŀ������״ͼ��������
//����һ��ö����ÿ������Ϊ��׼ֵͬʱ�����߽������� 
int largestRectangleArea1(vector<int>& heights) 
{
	int n = heights.size();
	vector<int> left(n, -1);		//��¼ÿ������߱��Լ�С���������
	vector<int> right(n, n);		//��¼ÿ�����ұ߱��Լ�С���������
	stack<int> s;

	//ά��һ��С->��ĵ���ջ  Ԫ�ؽ�ջʱ���м���
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

//�������������Ż� ����forѭ���Ż���һ��
int largestRectangleArea2(vector<int>& heights)
{
	int n = heights.size();
	vector<int> left(n, -1);		//��¼ÿ������߱��Լ�С���������
	vector<int> right(n, n);		//��¼ÿ�����ұ߱��Լ�С���������
	stack<int> s;

	//ά��һ��С->��ĵ���ջ  Ԫ�ؽ�ջʱ���м���left  Ԫ�س�ջʱ����right
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

//����������ʹ������ �ڵ���ջ���е�ͬʱ������´�
int largestRectangleArea3(vector<int>& heights)
{
	stack<int> st;
	heights.insert(heights.begin(), 0); // ����ͷ������Ԫ��0
	heights.push_back(0); // ����β������Ԫ��0
	st.push(0);
	int result = 0;
	//���ģ���ջ�е����ݱ���������ʱ��  �����ұ����Сֵ��������Сֵ���ǿ���ȷ����
	//ϸ�ڣ���ͬԪ�ز����� ǰ�᣺��λ����0
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