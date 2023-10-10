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