#include <string>
#include <vector>
using namespace std;

//最长回文子串问题

//方法一:动态规划      求子串可以用SubStr
bool dp[1001][1001];
string longestPalindrome1(string s)
{
    //dp[i][j]代表 i-j范围内是否是回文
    //dp[i][j] = s[i]==s[j]&&dp[i-1][j-1] 每个位置值依赖左下方
    int n = s.size();
    dp[n - 1][n - 1] = true;
    string ans; ans += s[0];
    for (int i = 0; i < n - 1; i++)
    {
        dp[i][i] = true;
        dp[i][i + 1] = (s[i] == s[i + 1]);
        if (dp[i][i + 1] && ans.size() != 2)
        {
            ans.clear();
            ans += s[i]; ans += s[i + 1];
        }
    }
    for (int k = 2; k < n; k++)
    {
        for (int i = 0; i < n - k; i++)
        {
            dp[i][i + k] = (s[i] == s[i + k]) && (dp[i + 1][i + k - 1]);
            if (dp[i][i + k] && ans.size() < k + 1)
            {
                ans.clear();
                for (int t = 0; t <= k; t++) ans += s[i + t];
            }
        }
    }
    return ans;


}
//方法二：中心扩展算法
string longestPalindrome2(string s)
{
    //假定以每个点作为中心点的情况
    int len = s.size();
    //得到修改后的字符串t
    string t; t.reserve(2 * len - 1);
    for (int i = 0; i < len - 1; i++)
    {
        t += s[i];
        t += '#';
    }
    t += s[len - 1];
    //枚举每个中心点作为开始
    string ans; ans += t[0];
    for (int i = 1; i < t.size() - 1; i++)
    {
        int l = i - 1, r = i + 1;
        int count = (t[i] != '#');
        while (l >= 0 && r < t.size() && t[l] == t[r])
        {
            if (t[l] != '#') count += 2;
            l--; r++;
        }
        if (count > ans.size())
        {
            ans.clear();
            l++; r--;
            for (int k = l; k <= r; k++)
            {
                if (t[k] != '#') ans += t[k];
            }
        }
    }
    return ans;

}


//方法三：Manacher算法 TODO
string longestPalindrome3(string s)
{
    
    return "";
}