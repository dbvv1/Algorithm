#include<vector>
using namespace std;

//24点游戏  可以使用运算符 + - * / 还有括号（） 问能否组成24点

//dfs思路：每次从cards中任意挑出两个数出来进行运算  知道只剩一个数的时候

bool dfs(int start, vector<int>& cards)
{
	if (start == 3)
	{
		if (cards[start] == 24) return true;
		return false;
	}

	//每次挑选两个数出来
	for (int i = start; i < 4; i++)
	{
		for (int j = start + 1; j < 4; j++)
		{
			//对这两个数进行运算 结果放到j中
			swap(cards[i], cards[start]);
			int f1 = cards[j];
			cards[j] = cards[start] + f1;
			bool p1 = dfs(start + 1, cards);
			cards[j] = cards[start] - f1;
			bool p2 = dfs(start + 1, cards);
			cards[j] = -cards[j];
			p2 |= dfs(start + 1, cards);
			cards[j] = cards[start] * f1;
			bool p3 = dfs(start + 1, cards);
			bool p4 = false;
			if (f1 != 0)
			{
				cards[j] = cards[start] / f1;
				p4 |= dfs(start + 1, cards);
			}
			if (cards[start] != 0)
			{
				cards[j] = f1 / cards[start];
				p4 |= dfs(start + 1, cards);
			}

			cards[j] = f1;
			swap(cards[i], cards[start]);
			if (p1 || p2 || p3 || p4) return true;

		}
	}
	return false;

}

bool judgePoint24(vector<int>& cards)
{
	return dfs(0, cards);
}