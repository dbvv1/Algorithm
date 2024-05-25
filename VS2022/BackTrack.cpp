#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
using namespace std;

vector<vector<int>> ans;   //答案数组
vector<int> track;		   //路径数组


//全排列1：返回所有的全排列 (直接使用原数组即可)
void permuteF1(int k, vector<int>& nums)
{
	if (k == nums.size())
	{
		ans.push_back(nums);
		return;
	}
	//选择第k个数是什么（和后面的数依次交换即可）
	for (int i = k; i < nums.size(); i++)
	{
		swap(nums[k], nums[i]);
		permuteF1(k + 1, nums);
		swap(nums[k], nums[i]);
	}
	
}

vector<vector<int>> permute(vector<int>& nums)
{
	permuteF1(0, nums);
	return ans;
}

//全排列2：返回不重复的全排列（关键，处理重复的情况）
//方法一：使用标记数组   方法二：遍历查看是否重复
void permuteF2(int k, vector<int>& nums)
{
	if (k == nums.size())
	{
		ans.push_back(nums);
		return;
	}
	//选择第k个数是什么（和后面的数依次交换即可）
	bool vis[21] = { false };
	for (int i = k; i < nums.size(); i++)
	{
		swap(nums[k], nums[i]);
		permuteF1(k + 1, nums);
		swap(nums[k], nums[i]);
	}
}

//另外一种方法：需要 对数组进行排序操作
bool used[10];
void permuteF22(int k, vector<int>& nums)
{
	if (k == nums.size())
	{
		ans.push_back(track);
		return;
	}
	for (int i = 0; i < nums.size(); i++)
	{
		//if (i > 0 && nums[i] == nums[i - 1] && used[i - 1] == true) continue; 也对 
		if (i > 0 && nums[i] == nums[i - 1] && used[i - 1] == false) continue;
		if (used[i] == false)
		{
			used[i] = true;
			track.push_back(nums[i]);
			permuteF22(k + 1, nums);
			track.pop_back();
			used[i] = false;
		}
	}
}

vector<vector<int>> permuteUnique(vector<int>& nums) 
{
	permuteF2(0, nums);
	return ans;
}






//组合：1-n 中 选择k个数      返回所有可能的组合

void conbineF1(int i, int n,int k)
{
	if (track.size() > k) return;
	if (i > n)
	{
		if (track.size() == k) ans.push_back(track);
		return;
	}
	//每个数选或不选
	track.push_back(i);
	conbineF1(i + 1, n, k);
	track.pop_back();
	conbineF1(i + 1, n, k);

}

void conbineF2(int i, int n, int k)
{
	if (i == k)
	{
		ans.push_back(track);
		return;
	}
	int start = i == 0 ? 1 : track[i - 1] + 1;
	for (int x = start; x <= n; x++)
	{
		track[i] = x;
		conbineF2(i + 1, n, k);
	}
}

vector<vector<int>> combine(int n, int k)
{
	track.resize(k, 0);
	conbineF2(0, n, k);
	return ans;
}


//组合总和一：   完全背包问题
void combinationSumF(int x, int target, vector<int>& candidates)
{
	if (target < 0) return;
	if (x == candidates.size())
	{
		if (target == 0) ans.push_back(track);
		return;
	}
	int count = 0;
	for (int k = 0; k * candidates[x] <= target; k++)
	{
		combinationSumF(x + 1, target - k * candidates[x], candidates);
		track.push_back(candidates[x]);
		count++;
	}
	//for (int k = 1; k<=(target)/candidates[x] + 1; k++) track.pop_back(); 也对
	while (count--)track.pop_back();
}

vector<vector<int>> combinationSum(vector<int>& candidates, int target)
{
	combinationSumF(0, target, candidates);
	return ans;
}

//组合总和2：   01背包问题，每个数只能选一个，不能包含重复的解
bool used2[101];
void combinationSum2F1(int x, int target, vector<int>& candidates)
{
	if (target < 0) return;
	if (x == candidates.size())
	{
		if (target == 0) ans.push_back(track);
		return;
	}
	if (x > 0 && candidates[x] == candidates[x - 1] && used2[x - 1] == false)
	{
		combinationSum2F1(x + 1, target, candidates);
		return;
	}
	//每个数选或不选
	used2[x] = true;
	track.push_back(candidates[x]);
	combinationSum2F1(x + 1, target - candidates[x], candidates);
	used2[x] = false;
	track.pop_back();
	combinationSum2F1(x + 1, target, candidates);

}

void combinationSum2F2(vector<int>& candidates, int target, int sum, int startIndex) {
	if (sum == target) {
		ans.push_back(track);
		return;
	}
	for (int i = startIndex; i < candidates.size() && sum + candidates[i] <= target; i++)
	{
		if (i > startIndex && candidates[i] == candidates[i - 1]) continue;
		sum += candidates[i];
		track.push_back(candidates[i]);
		combinationSum2F2(candidates, target, sum, i + 1);
		sum -= candidates[i];
		track.pop_back();
	}
}

vector<vector<int>> combinationSum2(vector<int>& candidates, int target)
{
	sort(candidates.begin(), candidates.end());
	combinationSum2F1(0, target, candidates);
	return ans;

}

//电话号码的组合:
void letterCombinationsF(vector<string>& combinations, const unordered_map<char, string>& phoneMap, const string& digits, int index, string& combination) {
	if (index == digits.length()) {
		combinations.push_back(combination);
	}
	else {
		char digit = digits[index];
		const string& letters = phoneMap.at(digit);
		for (const char& letter : letters) {
			combination.push_back(letter);
			letterCombinationsF(combinations, phoneMap, digits, index + 1, combination);
			combination.pop_back();
		}
	}
}
vector<string> letterCombinations(string digits) {
	vector<string> combinations;
	if (digits.empty()) {
		return combinations;
	}
	unordered_map<char, string> phoneMap{
		{'2', "abc"},
		{'3', "def"},
		{'4', "ghi"},
		{'5', "jkl"},
		{'6', "mno"},
		{'7', "pqrs"},
		{'8', "tuv"},
		{'9', "wxyz"}
	};
	string combination;
	letterCombinationsF(combinations, phoneMap, digits, 0, combination);
	return combinations;
}


//分割回文串
vector<vector<string>> ans2;
vector<string> track2;
bool ishuiwen(string& s)
{
	int l = 0, r = s.size() - 1;
	while (l < r)
	{
		if (s[l] != s[r]) return false;
		l++;
		r--;
	}
	return true;
}

void partitionF(int k, string& s)
{
	if (k == s.size())
	{
		ans2.push_back(track2);
		return;
	}
	string x;
	x += s[k];
	track2.push_back(x);
	partitionF(k + 1, s);
	track2.pop_back();
	for (int j = k + 1; j < s.size(); j++)
	{
		x += s[j];
		if (ishuiwen(x))
		{
			track2.push_back(x);
			partitionF(j + 1, s);
			track2.pop_back();
		}
	}

}

vector<vector<string>> partition(string s)
{
	partitionF(0, s);
	return ans2;
}

//N皇后问题
int x[10]; //第i行的皇后放置在了 x[i]的位置上
//将皇后放置在k行的x[k]上是否可行（是否不和前面的位置冲突）
bool isok(int k)
{
	//判断同列和同斜线
	for (int i = 0; i < k; i++)
	{
		if (x[i] == x[k] || (abs(k - i) == abs(x[k] - x[i]))) return false;
	}
	return true;
}
void solveNQueensF(int k,int n)
{
	if (k == n)
	{
		vector<string>t(n, string(n, '.'));
		for (int i = 0; i < n; i++)
		{
			t[i][x[i]] = 'Q';
		}
		ans2.emplace_back(t);
		return;
	}
	//选择皇后的位置
	for (int i = 0; i < n; i++)
	{
		x[k] = i;
		if (isok(k))
		{
			solveNQueensF(k + 1, n);
		}
	}
}

vector<vector<string>> solveNQueens(int n)
{
	solveNQueensF(0, n);
	return ans2;
}