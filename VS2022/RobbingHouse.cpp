#include<vector>
#include <functional>
using namespace std;

//����һ��רҵ��С͵���ƻ�͵���ؽֵķ��ݡ�
//����������ڵķ�����ͬһ���ϱ�С͵���룬ϵͳ���Զ�������

//��ҽ���1 
//dp[i]��ʾǰi-1�䷿����͵�������ֵ
int rob1(vector<int>& nums) 
{
	if (nums.size() == 0) return 0;
	if (nums.size() == 1) return nums[0];
	int ans = max(nums[0], nums[1]);
	//vector<int> dp(nums.size());
	//dp[0] = nums[0];
	//dp[1] = ans;
	//for (int i = 2; i < nums.size(); i++)
	//{
	//	//������ѡ�� ͵i �� ��͵i
	//	dp[i] = max(dp[i - 1], nums[i] + dp[i - 2]);
	//	ans = max(ans, dp[i]);
	//}
	int a = nums[0], b = ans;
	for (int i = 2; i < nums.size(); i++)
	{
		int t = b;
		b = max(b, a + nums[i]);
		a = t;
		ans = max(ans, b);
	}
	return ans;
}

//��ҽ���2  �ı䣺���������ǻ��ε�
//��rob1�Ļ����ϣ� ���������͵��һ�䷿����͵��һ�䷿ �ֱ���㼴��

int rob1(vector<int>& nums, int start, int end) //����rob1���ı䣺�����˷�Χ 
{
	if (start>end) return 0;
	if (start == end) return nums[start];
	int ans = max(nums[start], nums[start + 1]);
	int a = nums[start], b = ans;
	for (int i = start + 2; i <= end; i++)
	{
		int t = b;
		b = max(b, a + nums[i]);
		a = t;
		ans = max(ans, b);
	}
	return ans;
}

int rob2(vector<int>& nums)
{
	if (nums.size() == 0) return 0;
	if (nums.size() == 1) return nums[0];
	int p1 = nums[0] + rob1(nums, 2, nums.size() - 2);
	int p2 = rob1(nums, 1, nums.size() - 1);
	return max(p1, p2);
}

//��ҽ���3 �ı䣺���ϵķ�ʽ,����͵�������ڵĽ��
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};
 
struct States
{
	int select;     //ѡ��
	int notSelect;  //û��ѡ��
	States(int x = 0, int y = 0) :select(x), notSelect(y) {};
};

States f(TreeNode* root)
{
	if (root == nullptr) return States(0, 0);
	States left = f(root->left);
	States right = f(root->right);
	return States(root->val + left.notSelect + right.notSelect,
		max(left.select, left.notSelect) + max(right.select, right.notSelect));
}

int rob3(TreeNode* root)
{
	States ans = f(root);
	return max(ans.select, ans.notSelect);
}

//��ҽ���4   С͵������ֵ������ֵ����nums[i]����͵  k��ʾС͵����Ҫ͵k�䷿�� ��С͵����С������
bool check(vector<int>& nums, int cap, int k)
{
	int ans = 0;
	int i = 0;
	while (i < nums.size())
	{
		if (cap >= nums[i])
		{
			ans++; if (ans >= k) return true;
			i += 2;
		}
		else i++;
	}
	return ans >= k;
}

int minCapability(vector<int>& nums, int k) 
{
	if (nums.size() == 1) return nums[0];
	//���ִ𰸷�
	int l = INT_MAX;
	int r = INT_MIN;
	for (int i = 0; i < nums.size(); i++)
	{
		l = min(nums[i], l);
		r = max(nums[i], r);
	}
	int ans = r;
	while (l <= r)
	{
		int mid = l + (r - l) / 2;
		if (check(nums, mid, k))
		{
			ans = mid;
			r = mid - 1;
		}
		else l = mid + 1;
	}
	return ans;
}

//�ָ�������������ǡ������������ֵ��������
void recoverTree(TreeNode* root)
{
	//����һ����������õ�����
	vector<TreeNode*> nodes;

	function<void(TreeNode*)> f = [&](TreeNode* root)
	{
		if (root == nullptr) return;
		f(root->left);
		nodes.push_back(root);
		f(root->right);
	};
	f(root);
	nodes.shrink_to_fit();

	for (int i = 0; i < nodes.size(); i++)
	{
		if (nodes[i]->val > nodes[i + 1]->val)
		{
			int j = i + 1;
			while (j < nodes.size() && nodes[j]->val <= nodes[j - 1]->val) j++; j--;
			int t = nodes[i]->val;
			nodes[i]->val = nodes[j]->val;
			nodes[j]->val = t;
			break;
		}
	}


}