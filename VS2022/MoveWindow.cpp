#include<vector>
#include<string>
#include <unordered_map>
using namespace std;

//返回总和大于等于 target 的长度最小的连续子数组
int minSubArrayLen(int target, vector<int>& nums)
{
    int ans = INT_MAX;
    int sum = 0;
    int l = 0;
    int r = -1;
    while (1)
    {
        if (++r == nums.size()) break;
        sum += nums[r];

        while (sum >= target)
        {
            ans = min(ans, r - l + 1);
            sum -= nums[l];
            l++;
        }

    }

    return ans == INT_MAX ? 0 : ans;

}

//无重复字符的最短子串
int lengthOfLongestSubstring(string s)
{
    int l = 0, r = -1;
    int ans = 0;
    bool hash[129] = { false };
    while (1)
    {
        if (++r == s.size()) return ans;
        if (hash[s[r]])
        {
            while (s[l] != s[r])
            {
                hash[s[l]] = false;
                l++;
            }
            l++;
        }
        else hash[s[r]] = true;
        ans = max(ans, r - l + 1);
    }
    return ans;
}

//最小覆盖子串
string minWindow(string s, string t)
{
    int rest = t.size();
    string ans;
    if (rest > s.size()) return  ans;

    int hash[129] = { 0 };
    for (int i = 0; i < t.size(); i++) hash[t[i]]++;

    int l = 0, r = -1;
    while (1)
    {
        if (++r == s.size()) break;

        hash[s[r]]--;
        if (hash[s[r]] >= 0)
        {
            rest--;
            if (rest == 0)
            {
                //向让l往左移动
                while (hash[s[l]] < 0)
                {
                    hash[s[l]]++;
                    l++;
                }
                if (ans == "" || r - l + 1 < ans.size())
                    ans = s.substr(l, r - l + 1);
                hash[s[l]]++; l++; rest++;
            }
        }

    }
    return ans;

}

//串联所有单词的子串 
vector<int> findSubstring(string& s, vector<string>& words) 
{
    vector<int> res;
    //m单词的个数，n每个单词的长度
    int m = words.size(), n = words[0].size(), ls = s.size();
    //以i作为串联的起始点开始遍历（同时在内部遍历处理i+n，i+2n ...）
    for (int i = 0; i < n && i + m * n <= ls; ++i)
    {
        unordered_map<string, int> differ;
        for (int j = 0; j < m; ++j) 
        {
            ++differ[s.substr(i + j * n, n)];
        }
        for (string& word : words) 
        {
            if (--differ[word] == 0) 
            {
                differ.erase(word);
            }
        }
        for (int start = i; start < ls - m * n + 1; start += n) 
        {
            if (start != i) 
            {
                string word = s.substr(start + (m - 1) * n, n);
                if (++differ[word] == 0) 
                {
                    differ.erase(word);
                }
                word = s.substr(start - n, n);
                if (--differ[word] == 0) 
                {
                    differ.erase(word);
                }
            }
            if (differ.empty()) {
                res.emplace_back(start);
            }
        }
    }
    return res;
}