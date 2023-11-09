#include<vector>
#include<string>
#include<functional>
#include <unordered_set>
using namespace std;


//题目一：复原IP地址
//有效 IP 地址 正好由四个整数（每个整数位于 0 到 255 之间组成，且不能含有前导 0），整数之间用 '.' 分隔。

vector<string> ans;// 记录结果
string t;          // 记录中间的路径

// 判断字符串s在左闭又闭区间[start, end]所组成的数字是否合法
bool isValid(const string& s, int start, int end) {
    if (start > end) {
        return false;
    }
    if (s[start] == '0' && start != end) { // 0开头的数字不合法
        return false;
    }
    int num = 0;
    for (int i = start; i <= end; i++) {
        if (s[i] > '9' || s[i] < '0') { // 遇到非数字字符不合法
            return false;
        }
        num = num * 10 + (s[i] - '0');
        if (num > 255) { // 如果大于255了不合法
            return false;
        }
    }
    return true;
}


//方法一： startIndex: 搜索的起始位置，pointNum:添加逗点的数量
void restoreIpAddressesF(string& s, int startIndex, int pointNum)
{
    if (pointNum == 3) 
    {   // 逗点数量为3时，分隔结束
        // 判断第四段子字符串是否合法，如果合法就放进result中
        if (isValid(s, startIndex, s.size() - 1)) ans.push_back(s);
        return;
    }
    for (int i = startIndex; i < s.size(); i++) 
    {
        if (isValid(s, startIndex, i)) { // 判断 [startIndex,i] 这个区间的子串是否合法
            s.insert(s.begin() + i + 1, '.');  // 在i的后面插入一个逗点
            restoreIpAddressesF(s, i + 2, pointNum + 1);   // 插入逗点之后下一个子串的起始位置为i+2                  
            s.erase(s.begin() + i + 1);         // 回溯删掉逗点
        }
        else break; // 不合法，直接结束本层循环
    }
}

//方法二：当前来到了下标start，要处理第k个数时的情况  核心：在递归中间新增变量z记录中间状态

vector<string> restoreIpAddresses(string s)
{
    restoreIpAddressesF(s, 0, 0);
    function<void(int, int, string&)> f = [&f](int start, int k, string& s)
    {
        if (k > 5) return;
        if (start == s.size())
        {
            t.pop_back();
            if (k == 5) ans.push_back(t);
            return;
        }
        //以下标k的字符开始进行IP的分割
        int cur = 0;
        string z = t;
        for (int i = start; i < s.size(); i++)
        {
            cur = cur * 10 + s[i] - '0';
            if (cur > 255) break;
            t.push_back(s[i]);
            z.push_back(s[i]);
            t.push_back('.');
            f(i + 1, k + 1, s);
            t = z;
            if (cur == 0) break;
        }
    };
    return ans;
}

//字符串解码
string decodeString(string s)
{
    function<pair<string, int>(int, string&)> p = [&p](int k, string& s)
    {
        if (k == s.size()) return pair<string, int>("", s.size());
        if (s[k] == ']') return pair<string, int>("", k + 1);
        string ans;
        int next = k + 1;
        //当前字符是数字
        if (s[k] >= '0' && s[k] <= '9')
        {
            int count = 0;
            while (s[k] >= '0' && s[k] <= '9')
            {
                count = count * 10 + s[k] - '0';
                k++;
            }
            auto t = p(k + 1, s);
            for (int i = 1; i <= count; i++) ans += t.first;
            next = t.second;
        }
        //当前字符是小写字母
        else if (s[k] >= 'a' && s[k] <= 'z')
        {
            ans += s[k];
        }

        auto t = p(next, s);
        return pair<string, int>(ans + t.first, t.second);
    };
    return p(0, s).first;
}


//删除最小数量的无效括号 使得输入的字符串变成有效的括号串

//方法一：纯暴力回溯 + 键值
vector<string> removeInvalidParentheses1(string s)
{
    vector<string> ans;
    unordered_set<string> hash;
    //当前处理到第k个位置 左边还剩下preLeft没有配对

    function<void(int, int, int, string&)> f = [&](int k, int preleft, int del, string& s)
    {
        if (preleft < 0) return;
        if (ans.size() != 0 && s.size() - del < ans[0].size()) return;
        if (k == s.size())
        {
            if (preleft == 0)
            {
                string t;
                for (int i = 0; i < s.size(); i++) if (s[i] != '.') t += s[i];
                if (hash.find(t) != hash.end()) return;
                if (ans.size() == 0 || ans[0].size() < t.size())
                {
                    ans.clear();
                    hash.clear();
                    ans.push_back(t);
                    hash.insert(t);
                }
                else if (ans[0].size() == t.size())
                {
                    ans.push_back(t);
                    hash.insert(t);
                }
            }
            return;
        }
        //如果当前字符是字母的话 直接跳过
        if (s[k] >= 'a' && s[k] <= 'z')
        {
            f(k + 1, preleft, del, s);
        }
        else
        {
            if (s[k] == '(')
            {
                //选择不删除
                f(k + 1, preleft + 1, del, s);
                //选择删除
                s[k] = '.';
                f(k + 1, preleft, del + 1, s);
                s[k] = '(';
            }
            else
            {
                //选择不删除
                f(k + 1, preleft - 1, del, s);
                //选择删除
                s[k] = '.';
                f(k + 1, preleft, del + 1, s);
                s[k] = ')';
            }
        }
    };
    f(0, 0, 0, s);
    return ans;

}


//方法二：预处理要删除的括号个数 + 暴力回溯 + 剪枝
vector<string> removeInvalidParentheses2(string s)
{
    vector<string> ans;
    unordered_set<string> hash;
    //预处理：利用括号匹配的规则求出该字符串 sss 中最少需要去掉的左括号的数目 和 右括号的数目
    int lremove = 0;
    int rremove = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '(') lremove++;
        else if (s[i] == ')')
        {
            if (lremove == 0) rremove++;
            else lremove--;
        }
    }
    //当前处理到第k个位置 左边还剩下preLeft没有配对
    function<void(int, int, int, int, string&)> f = [&](int k, int preleft, int ldel, int rdel, string& s)
    {
        if (preleft < 0) return;
        if (ldel < 0 || ldel> s.size() - k) return;
        if (rdel < 0 || rdel>s.size() - k) return;
        if (k == s.size())
        {
            if (preleft == 0 && ldel == 0 && rdel == 0)
            {
                string t;
                for (int i = 0; i < s.size(); i++) if (s[i] != '.') t += s[i];
                if (hash.find(t) != hash.end()) return;
                hash.insert(t);
                ans.push_back(std::move(t));
            }
            return;
        }
        //如果当前字符是字母的话 直接跳过
        if (s[k] >= 'a' && s[k] <= 'z')
        {
            f(k + 1, preleft, ldel, rdel, s);
        }
        else
        {
            if (s[k] == '(')
            {
                //选择不删除
                f(k + 1, preleft + 1, ldel, rdel, s);
                //选择删除
                s[k] = '.';
                f(k + 1, preleft, ldel - 1, rdel, s);
                s[k] = '(';
            }
            else
            {
                //选择不删除
                f(k + 1, preleft - 1, ldel, rdel, s);
                //选择删除
                s[k] = '.';
                f(k + 1, preleft, ldel, rdel - 1, s);
                s[k] = ')';
            }
        }
    };
    f(0, 0, lremove, rremove, s);
    return ans;

}