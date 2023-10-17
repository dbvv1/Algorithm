#include <bits/stdc++.h>
using namespace std;

//一副牌 能否全部由顺子打完
//方法一：暴力递归


int lengthOfLastWord(string s) 
{
	//求字符串中最后一个单词的长度
	int l = s.size() - 1;
	int r = s.size() - 1;
	while (s[l] == ' ')
	{
		l--;
		r--;
	}
	while (l >= 0 && s[l] != ' ') l--;

	if (l < 0 || s[l] != ' ') return 0;
	return r - l;
}

