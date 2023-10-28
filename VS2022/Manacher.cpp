#include <string>
#include <vector>
using namespace std;

//������Ӵ�����

//����һ:��̬�滮      ���Ӵ�������SubStr
bool dp[1001][1001];
string longestPalindrome1(string s)
{
    //dp[i][j]���� i-j��Χ���Ƿ��ǻ���
    //dp[i][j] = s[i]==s[j]&&dp[i-1][j-1] ÿ��λ��ֵ�������·�
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
//��������������չ�㷨
string longestPalindrome2(string s)
{
    //�ٶ���ÿ������Ϊ���ĵ�����
    int len = s.size();
    //�õ��޸ĺ���ַ���t
    string t; t.reserve(2 * len - 1);
    for (int i = 0; i < len - 1; i++)
    {
        t += s[i];
        t += '#';
    }
    t += s[len - 1];
    //ö��ÿ�����ĵ���Ϊ��ʼ
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


//��������Manacher�㷨 TODO
string longestPalindrome3(string s)
{
    
    return "";
}