#include<vector>
#include<string>
#include<functional>
#include <unordered_set>
using namespace std;


//��Ŀһ����ԭIP��ַ
//��Ч IP ��ַ �������ĸ�������ÿ������λ�� 0 �� 255 ֮����ɣ��Ҳ��ܺ���ǰ�� 0��������֮���� '.' �ָ���

vector<string> ans;// ��¼���
string t;          // ��¼�м��·��

// �ж��ַ���s������ֱ�����[start, end]����ɵ������Ƿ�Ϸ�
bool isValid(const string& s, int start, int end) {
    if (start > end) {
        return false;
    }
    if (s[start] == '0' && start != end) { // 0��ͷ�����ֲ��Ϸ�
        return false;
    }
    int num = 0;
    for (int i = start; i <= end; i++) {
        if (s[i] > '9' || s[i] < '0') { // �����������ַ����Ϸ�
            return false;
        }
        num = num * 10 + (s[i] - '0');
        if (num > 255) { // �������255�˲��Ϸ�
            return false;
        }
    }
    return true;
}


//����һ�� startIndex: ��������ʼλ�ã�pointNum:��Ӷ��������
void restoreIpAddressesF(string& s, int startIndex, int pointNum)
{
    if (pointNum == 3) 
    {   // ��������Ϊ3ʱ���ָ�����
        // �жϵ��Ķ����ַ����Ƿ�Ϸ�������Ϸ��ͷŽ�result��
        if (isValid(s, startIndex, s.size() - 1)) ans.push_back(s);
        return;
    }
    for (int i = startIndex; i < s.size(); i++) 
    {
        if (isValid(s, startIndex, i)) { // �ж� [startIndex,i] ���������Ӵ��Ƿ�Ϸ�
            s.insert(s.begin() + i + 1, '.');  // ��i�ĺ������һ������
            restoreIpAddressesF(s, i + 2, pointNum + 1);   // ���붺��֮����һ���Ӵ�����ʼλ��Ϊi+2                  
            s.erase(s.begin() + i + 1);         // ����ɾ������
        }
        else break; // ���Ϸ���ֱ�ӽ�������ѭ��
    }
}

//����������ǰ�������±�start��Ҫ�����k����ʱ�����  ���ģ��ڵݹ��м���������z��¼�м�״̬

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
        //���±�k���ַ���ʼ����IP�ķָ�
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

//�ַ�������
string decodeString(string s)
{
    function<pair<string, int>(int, string&)> p = [&p](int k, string& s)
    {
        if (k == s.size()) return pair<string, int>("", s.size());
        if (s[k] == ']') return pair<string, int>("", k + 1);
        string ans;
        int next = k + 1;
        //��ǰ�ַ�������
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
        //��ǰ�ַ���Сд��ĸ
        else if (s[k] >= 'a' && s[k] <= 'z')
        {
            ans += s[k];
        }

        auto t = p(next, s);
        return pair<string, int>(ans + t.first, t.second);
    };
    return p(0, s).first;
}


//ɾ����С��������Ч���� ʹ��������ַ��������Ч�����Ŵ�

//����һ������������ + ��ֵ
vector<string> removeInvalidParentheses1(string s)
{
    vector<string> ans;
    unordered_set<string> hash;
    //��ǰ������k��λ�� ��߻�ʣ��preLeftû�����

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
        //�����ǰ�ַ�����ĸ�Ļ� ֱ������
        if (s[k] >= 'a' && s[k] <= 'z')
        {
            f(k + 1, preleft, del, s);
        }
        else
        {
            if (s[k] == '(')
            {
                //ѡ��ɾ��
                f(k + 1, preleft + 1, del, s);
                //ѡ��ɾ��
                s[k] = '.';
                f(k + 1, preleft, del + 1, s);
                s[k] = '(';
            }
            else
            {
                //ѡ��ɾ��
                f(k + 1, preleft - 1, del, s);
                //ѡ��ɾ��
                s[k] = '.';
                f(k + 1, preleft, del + 1, s);
                s[k] = ')';
            }
        }
    };
    f(0, 0, 0, s);
    return ans;

}


//��������Ԥ����Ҫɾ�������Ÿ��� + �������� + ��֦
vector<string> removeInvalidParentheses2(string s)
{
    vector<string> ans;
    unordered_set<string> hash;
    //Ԥ������������ƥ��Ĺ���������ַ��� sss ��������Ҫȥ���������ŵ���Ŀ �� �����ŵ���Ŀ
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
    //��ǰ������k��λ�� ��߻�ʣ��preLeftû�����
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
        //�����ǰ�ַ�����ĸ�Ļ� ֱ������
        if (s[k] >= 'a' && s[k] <= 'z')
        {
            f(k + 1, preleft, ldel, rdel, s);
        }
        else
        {
            if (s[k] == '(')
            {
                //ѡ��ɾ��
                f(k + 1, preleft + 1, ldel, rdel, s);
                //ѡ��ɾ��
                s[k] = '.';
                f(k + 1, preleft, ldel - 1, rdel, s);
                s[k] = '(';
            }
            else
            {
                //ѡ��ɾ��
                f(k + 1, preleft - 1, ldel, rdel, s);
                //ѡ��ɾ��
                s[k] = '.';
                f(k + 1, preleft, ldel, rdel - 1, s);
                s[k] = ')';
            }
        }
    };
    f(0, 0, lremove, rremove, s);
    return ans;

}