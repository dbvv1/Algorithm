#include<vector>
using namespace std;


//埃氏筛
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

const int MAXN = 10000; // 根据需要设置最大值
int prime[MAXN]; // 存储质数的数组
bool isPrime[MAXN]; // 标记是否为质数，初始都为false

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



// 欧拉筛法求质数
void euler_sieve(int n)
{
	fill(isPrime, isPrime + n, true); // 初始化所有数字都视作素数（true）
	int p = 0; // 质数的数量
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