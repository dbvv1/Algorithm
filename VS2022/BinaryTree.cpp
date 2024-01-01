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

#pragma region  �����������ֱ�����ʽ(�ݹ� + ����)
//ǰ��ݹ�
void preorderTraversalF1(TreeNode* root)
{
	//�Ȳ������ڵ� �ٵݹ������ӽڵ�
	if (root == nullptr) return;
	ans.push_back(root->val);
	preorderTraversalF1(root->left);
	preorderTraversalF1(root->right);

}

//ǰ�����  ������
void preorderTraversalF2(TreeNode* root)
{
	if (root == nullptr) return;
	//����ջʵ��
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

//����ݹ�
void inorderTraversalF1(TreeNode* root)
{
	//�ȵݹ��� �ٲ������ڵ� �ٵݹ���
	if (root == nullptr) return;
	preorderTraversalF1(root->left);
	ans.push_back(root->val);
	preorderTraversalF1(root->right);

}

//�������   ������
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

//����ݹ�
void postorderTraversalF1(TreeNode* root)
{
	//�ȵݹ����� �ٲ��������
	if (root == nullptr) return;
	preorderTraversalF1(root->left);
	preorderTraversalF1(root->right);
	ans.push_back(root->val);

}

//�������  ������
void postorderTraversalF2(TreeNode* root)
{
	if (root == nullptr) return;
	//����ջʵ��
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

//ͳһʵ�ֵ����ֱ�����ʽ �����õ���ָ����б�ǣ�
void orderTraversal(TreeNode* root)
{
	//����ʵ��������� ������
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

//�������������ȣ�  ���� ���ҵݹ�Ľϴ�ֵ + 1
//��ת��������  �ݹ��� + �ݹ��� + swap(left,right)

//�ж϶�������Գ�
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

//��������ֱ�������ض����������������ڵ��������ֵ
//ת������߶ȵ�ͬʱ�����
int diameter;
int diameterOfBinaryTreeF(TreeNode* root) 
{
	if (root == nullptr) return 0;
	//���������������������������Խ
	int leftHeight = diameterOfBinaryTreeF(root->left) ;
	int rightHeight = diameterOfBinaryTreeF(root->right);
	diameter = max(diameter, leftHeight + rightHeight);     //��¼�����Ĵ�
	return max(leftHeight, rightHeight) + 1;
}

//�������� --> ����������   �����������
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
 
//�ж϶���������
//��ǰ�ڵ�Ϊroot ��ΧΪlow-up��ʾ �����������ֵ ����������Сֵ
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

//�����������е�kС��Ԫ��
int countNum = 0;
int kth;

void kthSmallestF(TreeNode* root, int k)
{
	if (root == nullptr) return;
	//�������
	kthSmallestF(root->left, k);
	if (++countNum == k) kth = root->val;
	kthSmallestF(root->right, k);
}

int kthSmallest(TreeNode* root, int k) 
{
	kthSmallestF(root, k);
	return kth;
}

//������������ͼ�� ����һ���������  ���������ݹ�
//�ݹ��˼·���ȵݹ��ұ� �ٵݹ���� ͬʱ����¼��һ��������ȵ�λ�ü�Ϊ�ò�����ҽ��
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

//ǰ�� + ���� ����������
TreeNode* buildTreeByPreAndIn(vector<int>& preorder, int l1, int r1, vector<int>& inorder, int l2, int r2,
	unordered_map<int, int>& hash)
{
	if (l1 > r1) return nullptr;
	TreeNode* root = new TreeNode(preorder[l1]);
	//ͨ�� ���� ���齫ǰ��������л���  1��������� 2��Ԥ���� ������ϣ��
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
	//ͨ�� ���� ���齫ǰ��������л���  1��������� 2��Ԥ���� ������ϣ��
	int k = hash[postorder[r1]];
	int leftNum = k - l2;
	int rightNum = r2 - k;
	root->left = buildTreeByPostAndIn(postorder, l1, r1 - rightNum - 1, inorder, l2, k - 1,hash);
	root->right = buildTreeByPostAndIn(postorder, r1 - rightNum, r1 - 1, inorder, k + 1, r2,hash);
	return root;

}
//���� + ���� ����������
TreeNode* buildTree2(vector<int>& inorder, vector<int>& postorder) 
{
	unordered_map<int, int> hash;
	for (int i = 0; i < inorder.size(); i++) hash[inorder[i]] = i;
	return buildTreeByPostAndIn(postorder, 0, postorder.size() - 1, inorder, 0, inorder.size() - 1,hash);
}


//·���ܺ�ϵ��

//1���ж�����·����=targetSum
bool hasPathSum1(TreeNode* root, int targetSum)
{
	if (root == nullptr) return false;
	if (root->left == nullptr && root->right == nullptr) return targetSum == root->val;
	return hasPathSum1(root->left, targetSum - root->val) || hasPathSum1(root->right, targetSum - root->val);
}

//2������������н��
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

//3:ͬ1 ����Ҫ�Ӹ��ڵ㿪ʼ������·�����������µ� ����·����Ŀ �ص�
//����һ��ö����ÿ�������Ϊ���ڵ�ʱ��ans Ȼ���ۼ�ans 
int pathSum3F1(TreeNode* root, long long targetSum)
{
	if (root == nullptr) return 0;
	int ans = 0;
	if (targetSum == root->val) ans++;
	ans += pathSum3F1(root->left, targetSum - root->val);
	ans += pathSum3F1(root->right, targetSum - root->val);

	return ans;

}

//��������ʹ��ǰ׺�͵ĸ���  ������� + ǰ׺��
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
	//ǰ׺�͵ķ���
	prefix[0] = 1;
	return pathSum3F2(root, 0, targetSum);
}

//�������������������
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
{
	if (root == nullptr || root == p || root == q) return root;
	TreeNode* left = lowestCommonAncestor(root->left, p, q);
	TreeNode* right = lowestCommonAncestor(root->right, p, q);
	if (left && right) return root;
	else if (left) return left;
	else return right;
}

//�������е����·����
//������ÿ�������Ϊ�������  ����߶ȵݹ麯���� ˳����½��
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

//�������������˳��չ��������Ϊ����ԭ���޸� left--preָ��  right->nextָ�룩
//˫ָ�� + �������
TreeNode* pre;
TreeNode* last;
//�����������������������ȫ�෴��˳��   ��  ��  ��
void flattenF2(TreeNode* root)
{
	if (root == nullptr) return;
	flattenF2(root->right);
	flattenF2(root->left);

	root->left = nullptr;
	root->right = last;

	last = root;

}

//����һ��ֱ�Ӳ��������������¼��һ����㣬���ұ���left��right
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


//��������Morrisʵ�ַ���������� ʵ��O��1�����Ӷ�

//�õ���̽ڵ㣺������������ڵ�
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