#include<vector>
#include<string>
#include<stack>
using namespace std;


bool isOperator(string& s)
{
    return s.size() == 1 && (s[0] == '+' || s[0] == '-' || s[0] == '*' || s[0] == '/');
}

bool isOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

//��Ŀһ���沨�����ʽ����׺���ʽ����ֵ
int evalRPN(vector<string>& tokens)
{
    //����ջʵ��
    //�������ּ���ջ�������������������
    stack<int> s;
    for (int i = 0; i < tokens.size(); i++)
    {
        //�����������
        if (isOperator(tokens[i]))
        {
            int y = s.top(); s.pop();
            int x = s.top(); s.pop();
            if (tokens[i][0] == '+') s.push(x + y);
            if (tokens[i][0] == '-') s.push(x - y);
            if (tokens[i][0] == '*') s.push(x * y);
            if (tokens[i][0] == '/') s.push(x / y);
        }
        //��������
        else
        {
            int num = 0;
            int start = tokens[i][0] == '-' ? 1 : 0;
            for (int j = start; j < tokens[i].size(); j++)
            {
                num = num * 10 + tokens[i][j] - '0';
            }
            if (tokens[i][0] == '-') num *= -1;
            s.push(num);
        }
    }
    return s.top();
}

//��Ŀ��������������ʵ��1    + - ������ ������ - ����������ʾһԪ�������

int calculate1(string s)
{
    stack<int> nums;
    stack<char> oper;

    int i = 0;
    while (i < s.size())
    {
        //�����ֵ����
        if (s[i] >= '0' && s[i] <= '9')
        {
            int num = 0;
            while (i < s.size() && s[i] >= '0' && s[i] <= '9')
            {
                i++;
                num = num * 10 + s[i] - '0';
            }
        }
        else
        {
            //�����������
            if (s[i] == '(')
            {
                oper.push('(');
            }
            //�����������
            else if (s[i] == ')')
            {
                //�������еķ���ֱ������һ��������
            }
            else if (s[i] == '+')
            {
                if (oper.empty() || oper.top() != '(')
                {
                    //���Խ�������
                }
                else oper.push('+');
            }
            else if (s[i] == '-')
            {
                if (nums.empty())
                {
                    //�÷��ű�����һԪ�����
                }
                else
                {
                    if (oper.empty() || oper.top() != '(')
                    {
                        //���Խ�������

                    }
                    else oper.push('-');
                }
            }
        }
    }
    return nums.top();

}

//��Ŀ��������������ʵ��2    + - * / ����û������
int calculate2(string s)
{

    return 0;
}

//��Ŀ�ģ��ۺϼ�����ʵ��   + - * / ������
int calculate3(string s)
{
    return 0;
}