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

//题目一：逆波兰表达式（后缀表达式）求值
int evalRPN(vector<string>& tokens)
{
    //令用栈实现
    //遇到数字即入栈，遇到符号则进行运算
    stack<int> s;
    for (int i = 0; i < tokens.size(); i++)
    {
        //遇到运算符号
        if (isOperator(tokens[i]))
        {
            int y = s.top(); s.pop();
            int x = s.top(); s.pop();
            if (tokens[i][0] == '+') s.push(x + y);
            if (tokens[i][0] == '-') s.push(x - y);
            if (tokens[i][0] == '*') s.push(x * y);
            if (tokens[i][0] == '/') s.push(x / y);
        }
        //遇到数字
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

//题目二：基本计算器实现1    + - 和括号 （其中 - 可以用来表示一元运算符）

int calculate1(string s)
{
    stack<int> nums;
    stack<char> oper;

    int i = 0;
    while (i < s.size())
    {
        //是数字的情况
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
            //如果是左括号
            if (s[i] == '(')
            {
                oper.push('(');
            }
            //如果是右括号
            else if (s[i] == ')')
            {
                //弹出所有的符号直到遇到一个左括号
            }
            else if (s[i] == '+')
            {
                if (oper.empty() || oper.top() != '(')
                {
                    //可以进行运算
                }
                else oper.push('+');
            }
            else if (s[i] == '-')
            {
                if (nums.empty())
                {
                    //该符号被用作一元运算符
                }
                else
                {
                    if (oper.empty() || oper.top() != '(')
                    {
                        //可以进行运算

                    }
                    else oper.push('-');
                }
            }
        }
    }
    return nums.top();

}

//题目三：基本计算器实现2    + - * / 但是没有括号
int calculate2(string s)
{

    return 0;
}

//题目四：综合计算器实现   + - * / 和括号
int calculate3(string s)
{
    return 0;
}