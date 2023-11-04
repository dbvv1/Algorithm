#include<vector>
using namespace std;

//24����Ϸ  ����ʹ������� + - * / �������ţ��� ���ܷ����24��

//dfs˼·��ÿ�δ�cards����������������������������  ֪��ֻʣһ������ʱ��

bool dfs(int start, vector<int>& cards)
{
	if (start == 3)
	{
		if (cards[start] == 24) return true;
		return false;
	}

	//ÿ����ѡ����������
	for (int i = start; i < 4; i++)
	{
		for (int j = start + 1; j < 4; j++)
		{
			//������������������ ����ŵ�j��
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