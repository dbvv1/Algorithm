#include<vector>
#include<stack>
#include<queue>
using namespace std;

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

vector<int> ans;

#pragma region  二叉树的三种遍历方式(递归 + 迭代)
//前序递归
void preorderTraversalF1(TreeNode* root)
{
	//先操作根节点 再递归左右子节点
	if (root == nullptr) return;
	ans.push_back(root->val);
	preorderTraversalF1(root->left);
	preorderTraversalF1(root->right);

}

//前序迭代  中左右
void preorderTraversalF2(TreeNode* root)
{
	if (root == nullptr) return;
	//利用栈实现
	stack<TreeNode*> s;
	s.push(root);
	while (!s.empty())
	{
		TreeNode* t = s.top(); s.pop();
		ans.push_back(t->val);
		if (t->right) s.push(t->right);
		if (t->left) s.push(t->left);
	}

}

//中序递归
void inorderTraversalF1(TreeNode* root)
{
	//先递归左 再操作根节点 再递归右
	if (root == nullptr) return;
	preorderTraversalF1(root->left);
	ans.push_back(root->val);
	preorderTraversalF1(root->right);

}

//中序迭代   左中右
void inorderTraversalF2(TreeNode* root)
{
	if (root == nullptr) return;
	stack<TreeNode*> s;
	TreeNode* pre = nullptr;
	TreeNode* cur = root;
	while (cur || !s.empty())
	{
		while (cur != nullptr)
		{
			s.push(cur);
			cur = cur->left;
		}
		pre = s.top();
		ans.push_back(s.top()->val); s.pop();
		cur = pre->right;
	}

}

//后序递归
void postorderTraversalF1(TreeNode* root)
{
	//先递归左右 再操作根结点
	if (root == nullptr) return;
	preorderTraversalF1(root->left);
	preorderTraversalF1(root->right);
	ans.push_back(root->val);

}

//后序迭代  左右中
void postorderTraversalF2(TreeNode* root)
{
	if (root == nullptr) return;
	//利用栈实现
	stack<TreeNode*> s;
	s.push(root);
	while (!s.empty())
	{
		TreeNode* t = s.top(); s.pop();
		ans.push_back(t->val);
		if (t->left) s.push(t->left);
		if (t->right) s.push(t->right);
	}
	reverse(ans.begin(), ans.end());
}

//统一实现的三种遍历方式 （利用到空指针进行标记）
void orderTraversal(TreeNode* root)
{
	//迭代实现中序遍历 左中右
	if (root == nullptr) return;
	stack<TreeNode*> s;
	s.push(root);
	while (!s.empty())
	{
		TreeNode* cur = s.top();
		if (cur != nullptr)
		{
			s.pop();
			if (cur->right) s.push(cur->right);
			s.push(cur);
			s.push(nullptr);
			if (cur->left) s.push(cur->left);
		}
		else
		{
			s.pop();
			ans.push_back(s.top()->val);
			s.pop();
		}
	}

	return;

}

#pragma endregion

//二叉树的最大深度：  返回 左右递归的较大值 + 1
//翻转二叉树：  递归左 + 递归右 + swap(left,right)

//判断二叉树轴对称
bool isSymmetricF(TreeNode* root1, TreeNode* root2)
{
	if (root1 == nullptr && root2 == nullptr)  return true;
	if (root1 == nullptr || root2 == nullptr) return false;
	return isSymmetricF(root1->left, root2->right) && isSymmetricF(root1->right, root2->left) && root1->val == root2->val;
}

bool isSymmetric(TreeNode* root)
{
	if (root == nullptr) return true;
	return isSymmetricF(root->left, root->right);
}

//二叉树的直径：返回二叉树中任意两个节点距离的最大值
//转化：求高度的同时计算答案
int diameter;
int diameterOfBinaryTreeF(TreeNode* root) 
{
	if (root == nullptr) return 0;
	//三种情况：左子树，右子树，跨越
	int leftHeight = diameterOfBinaryTreeF(root->left) ;
	int rightHeight = diameterOfBinaryTreeF(root->right);
	diameter = max(diameter, leftHeight + rightHeight);     //记录真正的答案
	return max(leftHeight, rightHeight) + 1;
}

//有序数组 --> 二叉搜索数   中序遍历即可
TreeNode* sortedArrayToBSTF(int l, int r, vector<int>& nums)
{
	if (l > r) return nullptr;
	int mid = l + (r - l) / 2;
	TreeNode* root = new TreeNode(nums[mid]);
	root->left = sortedArrayToBSTF(l, mid - 1, nums);
	root->right = sortedArrayToBSTF(mid + 1, r, nums);
	return root;
}

TreeNode* sortedArrayToBST(vector<int>& nums) 
{
	return sortedArrayToBSTF(0, nums.size() - 1, nums);
}
 
//判断二叉搜索树
//当前节点为root 范围为low-up表示 左子树的最大值 右子树的最小值
bool isValidBSTF(TreeNode* root, long long low, long long up)
{
	if (root == nullptr) return true;

	if (root->val <= low || root->val >= up) return false;

	return isValidBSTF(root->left, low, root->val) &&
		isValidBSTF(root->right, root->val, up);
}

bool isValidBST(TreeNode* root)
{
	return isValidBSTF(root, -2147483649, 2147483648);
}

//二叉搜索数中第k小的元素
int countNum = 0;
int kth;

void kthSmallestF(TreeNode* root, int k)
{
	if (root == nullptr) return;
	//中序遍历
	kthSmallestF(root->left, k);
	if (++countNum == k) kth = root->val;
	kthSmallestF(root->right, k);
}

int kthSmallest(TreeNode* root, int k) 
{
	kthSmallestF(root, k);
	return kth;
}

//二叉树的右视图： 方法一：层序遍历  方法二：递归
//递归的思路：先递归右边 再递归左边 同时：记录第一个到达深度的位置即为该层的最右结点
void helper(TreeNode* node, vector<int>& nums, int depth)
{
	if (node==nullptr) return;
	if (nums.size() == depth)  nums.push_back(node->val);
	helper(node->right, nums, depth + 1);
	helper(node->left, nums, depth + 1);
}
vector<int> rightSideView(TreeNode* root)
{
	vector<int> ans;
	helper(root, ans, 0);
	return ans;
}