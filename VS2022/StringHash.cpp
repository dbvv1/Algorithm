#include<string>
#include<unordered_map>
using namespace std;

//题目一：重复的DNA序列
//方法一： unordered_map<string,int>
//方法二： unordered_map<int,int>  将字符串转化为一个整数，利用位运算处理

const int L = 10;
unordered_map<char, int> bin = { {'A', 0}, {'C', 1}, {'G', 2}, {'T', 3} };
vector<string> findRepeatedDnaSequences(string s)
{
	vector<string> ans;
	int n = s.length();
	if (n <= L) {
		return ans;
	}
	int x = 0;
	for (int i = 0; i < L - 1; ++i) {
		x = (x << 2) | bin[s[i]];
	}
	unordered_map<int, int> cnt;
	for (int i = 0; i <= n - L; ++i) {
		//滑动窗口右移一个字符，1：x左移两位 2：加入新的字符 3：将高于20位上置0
		x = ((x << 2) | bin[s[i + L - 1]]) & ((1 << (L * 2)) - 1);
		if (++cnt[x] == 2) {
			ans.push_back(s.substr(i, L));
		}
	}
	return ans;
}

//题目二：