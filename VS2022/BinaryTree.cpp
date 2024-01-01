#include<vector>
#include<stack>
#include<queue>
#include<unordered_map>
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

//前序 + 中序 构建二叉数
TreeNode* buildTreeByPreAndIn(vector<int>& preorder, int l1, int r1, vector<int>& inorder, int l2, int r2,
	unordered_map<int, int>& hash)
{
	if (l1 > r1) return nullptr;
	TreeNode* root = new TreeNode(preorder[l1]);
	//通过 中序 数组将前序数组进行划分  1：遍历解决 2：预处理 创建哈希表
	int k = hash[preorder[l1]];
	int leftNum = k - l2;
	int rightNum = r2 - k;
	root->left = buildTreeByPreAndIn(preorder, l1 + 1, l1 + leftNum, inorder, l2, k - 1,hash);
	root->right = buildTreeByPreAndIn(preorder, l1 + leftNum + 1, r1, inorder, k + 1, r2,hash);
	return root;
	
}

TreeNode* buildTree1(vector<int>& preorder, vector<int>& inorder) 
{
	unordered_map<int, int> hash;
	for (int i = 0; i < inorder.size(); i++) hash[inorder[i]] = i;
	return buildTreeByPreAndIn(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1, hash);
}

TreeNode* buildTreeByPostAndIn(vector<int>& postorder, int l1, int r1, vector<int>& inorder, int l2, int r2,unordered_map<int,int>& hash)
{
	if (l1 > r1) return nullptr;
	TreeNode* root = new TreeNode(postorder[r1]);
	//通过 中序 数组将前序数组进行划分  1：遍历解决 2：预处理 创建哈希表
	int k = hash[postorder[r1]];
	int leftNum = k - l2;
	int rightNum = r2 - k;
	root->left = buildTreeByPostAndIn(postorder, l1, r1 - rightNum - 1, inorder, l2, k - 1,hash);
	root->right = buildTreeByPostAndIn(postorder, r1 - rightNum, r1 - 1, inorder, k + 1, r2,hash);
	return root;

}
//后序 + 中序 构建二叉树
TreeNode* buildTree2(vector<int>& inorder, vector<int>& postorder) 
{
	unordered_map<int, int> hash;
	for (int i = 0; i < inorder.size(); i++) hash[inorder[i]] = i;
	return buildTreeByPostAndIn(postorder, 0, postorder.size() - 1, inorder, 0, inorder.size() - 1,hash);
}


//路径总和系列

//1：判断有无路径和=targetSum
bool hasPathSum1(TreeNode* root, int targetSum)
{
	if (root == nullptr) return false;
	if (root->left == nullptr && root->right == nullptr) return targetSum == root->val;
	return hasPathSum1(root->left, targetSum - root->val) || hasPathSum1(root->right, targetSum - root->val);
}

//2：回溯求出所有结果
vector<vector<int>> ans2;
vector<int> pass;
void pathSum2F(TreeNode* root, int target)
{
	if (root->left == nullptr && root->right == nullptr)
	{
		if (target == 0) ans2.push_back(pass);
		return;
	}
	if (root->left != nullptr)
	{
		pass.push_back(root->left->val);
		pathSum2F(root->left, target - root->left->val);
		pass.pop_back();
	}
	if (root->right != nullptr)
	{
		pass.push_back(root->right->val);
		pathSum2F(root->right, target - root->right->val);
		pass.pop_back();
	}
}

vector<vector<int>> pathSum2(TreeNode* root, int targetSum)
{
	if (root == nullptr) return ans2;
	pass.push_back(root->val);
	pathSum2F(root, targetSum - root->val);
	return ans2;
}

//3:同1 不需要从根节点开始，但是路径必须是向下的 返回路径数目 重点
//方法一：枚举以每个结点作为根节点时的ans 然后累加ans 
int pathSum3F1(TreeNode* root, long long targetSum)
{
	if (root == nullptr) return 0;
	int ans = 0;
	if (targetSum == root->val) ans++;
	ans += pathSum3F1(root->left, targetSum - root->val);
	ans += pathSum3F1(root->right, targetSum - root->val);

	return ans;

}

//方法二：使用前缀和的概念  先序遍历 + 前缀和
unordered_map<long long, int> prefix;

int pathSum3F2(TreeNode* root, long long curr, int targetSum) {
	if (!root) {
		return 0;
	}

	int ret = 0;
	curr += root->val;
	if (prefix.count(curr - targetSum)) {
		ret = prefix[curr - targetSum];
	}

	prefix[curr]++;
	ret += pathSum3F2(root->left, curr, targetSum);
	ret += pathSum3F2(root->right, curr, targetSum);
	prefix[curr]--;

	return ret;
}

int pathSum3(TreeNode* root, int targetSum)
{
	//前缀和的方法
	prefix[0] = 1;
	return pathSum3F2(root, 0, targetSum);
}

//二叉树的最近公共祖先
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
{
	if (root == nullptr || root == p || root == q) return root;
	TreeNode* left = lowestCommonAncestor(root->left, p, q);
	TreeNode* right = lowestCommonAncestor(root->right, p, q);
	if (left && right) return root;
	else if (left) return left;
	else return right;
}

//二叉树中的最大路径和
//考虑以每个结点作为根的情况  在求高度递归函数中 顺便更新结果
int maxSum = INT_MIN;
int maxPathSumF(TreeNode* root)
{
	if (root == nullptr) return 0;
	int left = max(maxPathSumF(root->left), 0);
	int right = max(maxPathSumF(root->right), 0);

	maxSum = max(maxSum, left + right + root->val);

	return max(left, right) + root->val;
}

int maxPathSum(TreeNode* root) 
{
	maxPathSumF(root);
	return maxSum;
}

//按照先序遍历的顺序展开二叉树为链表（原地修改 left--pre指针  right->next指针）
//双指针 + 先序遍历
TreeNode* pre;
TreeNode* last;
//方法二：采用与先序遍历完全相反的顺序   右  左  中
void flattenF2(TreeNode* root)
{
	if (root == nullptr) return;
	flattenF2(root->right);
	flattenF2(root->left);

	root->left = nullptr;
	root->right = last;

	last = root;

}

//方法一：直接采用先序遍历，记录上一个结点，并且保留left和right
void flattenF1(TreeNode* root)
{
	if (root == nullptr) return;
	TreeNode* left = root->left;
	TreeNode* right = root->right;
	if (pre)
	{
		pre->left = nullptr;
		pre->right = root;
	}
	pre = root;
	flattenF1(left);
	flattenF1(right);
}

void flatten(TreeNode* root) {

	//flattenF1(root);
	flattenF2(root);
}


//二叉树的Morris实现反向中序遍历 实现O（1）复杂度

//得到后继节点：右子树的最左节点
TreeNode* getSuccessor(TreeNode* node) 
{
	TreeNode* succ = node->right;
	while (succ->left != nullptr && succ->left != node) {
		succ = succ->left;
	}
	return succ;
}

TreeNode* bstToGst(TreeNode* root)
{
	TreeNode* node = root;

	while (node != nullptr)
	{
		if (node->right == nullptr)
		{
			node = node->left;
		}
		else 
		{
			TreeNode* succ = getSuccessor(node);
			if (succ->left == nullptr)
			{
				succ->left = node;
				node = node->right;
			}
			else 
			{
				succ->left = nullptr;
				node = node->left;
			}
		}
	}

	return root;
}