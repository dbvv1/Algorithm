#include<vector>
#include<set>
#include <stack>
using namespace std;

//给你一个整数数组 nums ，数组中共有 n 个整数。132 模式的子序列 由三个整数 nums[i]、nums[j] 和 nums[k] 组成，并同时满足：i < j < k 和 nums[i] < nums[k] < nums[j] 。 左边的数小于右边的数  右边的数小于中间的数

//方法一：枚举中间那个最大的值 使用有序集合 multiset
bool find132patternF1(vector<int>& nums) {
	int n = nums.size();
	if (n < 3) return;
	// 左侧最小值
	int left_min = nums[0];
	// 右侧所有元素
	multiset<int> right_all;

	for (int k = 2; k < n; ++k) {
		right_all.insert(nums[k]);
	}

	for (int j = 1; j < n - 1; ++j) {
		if (left_min < nums[j]) {
			auto it = right_all.upper_bound(left_min);
			if (it != right_all.end() && *it < nums[j]) {
				return true;
			}
		}
		left_min = min(left_min, nums[j]);
		right_all.erase(right_all.find(nums[j + 1]));
	}

	return false;
}

//方法二：从右向左枚举最小值 维护一个递减的单调栈 同时记录出栈的最大值k (k代表132中的2)
bool find132pattern(vector<int>& nums)
{
	//k是已经出栈的元素，说明在 k的左边一定有比k要大的元素  因此 j k 是满足的
	//只要满足nums[i]< k 说明满足了132的结构
	//为什么k要是出栈的最大元素呢？ 因为要尽可能的满足k要比nums[i]要大
	int n = nums.size();
	stack<int> s;
	int k = INT_MIN;
	s.push(nums[n - 1]);
	for (int i = n - 1; i >= 0; i--)
	{
		if (nums[i] < k) return true;
		while (!s.empty() && nums[i] > s.top())
		{
			k = max(k, s.top());
			s.pop();
		}
		if (!s.empty() && nums[i] == s.top()) continue;

		s.push(nums[i]);

	}
	return false;

}

//你有两个字符串，即pattern和value。 pattern字符串由字母"a"和"b"组成，用于描述字符串中的模式。例如，字符串"catcatgocatgo"匹配模式"aabab"（其中"cat"是"a"，"go"是"b"），该字符串也匹配像"a"、"ab"和"b"这样的模式。但需注意"a"和"b"不能同时表示相同的字符串。编写一个方法判断value字符串是否匹配pattern字符串。  数据范围为10^3
bool patternMatching(string pattern, string value)
{
	//pattern中只包含 a b 表示格式
	//暴力枚举 a 的所有可能
	int counta = 0;
	int countb = 0;
	int ak = -1; int prea1 = 0, preb1 = 0;//a第一次出现的位置 同时记录之前有几个a b
	int bk = -1; int prea2 = 0, preb2 = 0;//b第一出现的位置   同时记录之前有几个a b
	for (int i = 0; i < pattern.size(); i++)
	{
		if (pattern[i] == 'a')
		{
			if (ak == -1)
			{
				prea1 = counta;
				preb1 = countb;
				ak = i;
			}
			counta++;
		}
		else
		{
			if (bk == -1)
			{
				prea2 = counta;
				preb2 = countb;
				bk = i;
			}
			countb++;
		}

	}
	if (value == "") return counta == 0 || countb == 0; //特判空串的情况
	for (int i = 0; i <= value.size(); i++)
	{
		//a的长度为i 可以推出b的长度
		int lena = i;
		int lenb;
		if (countb != 0 && lena * counta > value.size()) break; //放置莫名其妙的溢出，提前判断是否还容得下b
		if (countb == 0) lenb = 0;
		else lenb = (value.size() - lena * counta) / countb;
		//进行实际的匹配过程
		string a; string b; a.reserve(lena); b.reserve(lenb);
		if (ak != -1)
		{
			//推算出a
			int start = lena * prea1 + lenb * preb1;
			a = value.substr(start, lena);
		}
		if (bk != -1)
		{
			//推算出b
			int start = lena * prea2 + lenb * preb2;
			b = value.substr(start, lenb);
		}
		if (a == b) continue;
				string ans; ans.reserve(value.size());
		for (int j = 0; j < pattern.size(); j++)
		{
			//模拟生成的结果
			if (pattern[j] == 'a') ans += a;
			else ans += b;
		}
		if (ans == value) return true;
	}
	return false;
}


bool patternMatching2(string pattern, string value) {
	int count_a = 0, count_b = 0;
	for (char ch : pattern) {
		if (ch == 'a') {
			++count_a;
		}
		else {
			++count_b;
		}
	}
	if (count_a < count_b) {
		swap(count_a, count_b);
		for (char& ch : pattern) {
			ch = (ch == 'a' ? 'b' : 'a');
		}
	}
	if (value.empty()) {
		return count_b == 0;
	}
	if (pattern.empty()) {
		return false;
	}
	for (int len_a = 0; count_a * len_a <= value.size(); ++len_a) {
		int rest = value.size() - count_a * len_a;
		if ((count_b == 0 && rest == 0) || (count_b != 0 && rest % count_b == 0)) {
			int len_b = (count_b == 0 ? 0 : rest / count_b);
			int pos = 0;
			bool correct = true;
			string value_a, value_b;
			for (char ch : pattern) {
				if (ch == 'a') {
					string sub = value.substr(pos, len_a);
					if (!value_a.size()) {
						value_a = move(sub);
					}
					else if (value_a != sub) {
						correct = false;
						break;
					}
					pos += len_a;
				}
				else {
					string sub = value.substr(pos, len_b);
					if (!value_b.size()) {
						value_b = move(sub);
					}
					else if (value_b != sub) {
						correct = false;
						break;
					}
					pos += len_b;
				}
			}
			if (correct && value_a != value_b) {
				return true;
			}
		}
	}
	return false;
}
