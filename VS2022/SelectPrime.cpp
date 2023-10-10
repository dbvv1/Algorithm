#include<vector>
using namespace std;


//����ɸ
vector<int> SeletePrime1(int n)
{
	vector<int> st(n, 0);
	st[0] = st[1] = 1;
	for (int i = 2; i * i <= n; i++)
	{
		for (int j = i * i; j <= n; j += i)
			st[j] = 1;
	}
	vector<int> ans;
	for (int i = 2; i <= n; i++)
		if (st[i] == 0) ans.push_back(i);
	return ans;
}

const int MAXN = 10000; // ������Ҫ�������ֵ
int prime[MAXN]; // �洢����������
bool isPrime[MAXN]; // ����Ƿ�Ϊ��������ʼ��Ϊfalse

void SeletePrime2(int n)
{
	fill(isPrime, isPrime + n, true);
	isPrime[0] = isPrime[1] = 0;
	for (int i = 2; i <= n / i; i++)
	{
		for (int j = i * i; j <= n; j += i)
			isPrime[j] = 0;
	}
}



// ŷ��ɸ��������
void euler_sieve(int n)
{
	fill(isPrime, isPrime + n, true); // ��ʼ���������ֶ�����������true��
	int p = 0; // ����������
	for (int i = 2; i <= n; ++i)
	{
		if (isPrime[i]) 
		{
			prime[p++] = i;
		}
		for (int j = 0; j < p && i * prime[j] <= n; ++j) 
		{
			isPrime[i * prime[j]] = false;
			if (i % prime[j] == 0) break;
		}
	}
}