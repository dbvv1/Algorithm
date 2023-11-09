#include<vector>
#include <functional>
using namespace std;

//你是一个专业的小偷，计划偷窃沿街的房屋。
//如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。

//打家劫舍1 
//dp[i]表示前i-1间房屋能偷到的最大值
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
	//	//有两种选择 偷i 和 不偷i
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

//打家劫舍2  改变：房间现在是环形的
//在rob1的基础上， 两种情况，偷第一间房，不偷第一间房 分别计算即可

int rob1(vector<int>& nums, int start, int end) //重载rob1，改变：增加了范围 
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

//打家劫舍3 改变：树上的方式,不能偷树上相邻的结点
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
	int select;     //选择
	int notSelect;  //没有选择
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

//打家劫舍4   小偷有能力值，能力值大于nums[i]才能偷  k表示小偷至少要偷k间房屋 求小偷的最小能力数
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
	//二分答案法
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

//恢复二叉搜索树：恰好由两个结点的值被交换了
void recoverTree(TreeNode* root)
{
	//方法一：中序遍历得到序列
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