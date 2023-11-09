#include <climits>
#include <stdlib.h>

//题目一：不用 + 实现 加法
int add(int a, int b) {
	while (b != 0) {
		int carry = (unsigned int)(a & b) << 1; // 计算进位
		a = a ^ b; // 计算无进位加法结果
		b = carry; // 将进位赋值给b，在下一次循环中与a相加
	}
	return a;
}

//题目二：不用 / 实现 除法
//方法一：允许使用无符号整数 unsigned int
int divide1(int a, int b) {
	if (a == INT_MIN && b == -1) return INT_MAX;

	int sign = ((a > 0) ^ (b > 0)) ? -1 : 1;

	unsigned int ua = abs(a);
	unsigned int ub = abs(b);
	unsigned int res = 0;
	for (int i = 31; i >= 0; i--) {
		if ((ua >> i) >= ub) {
			ua = ua - (ub << i);
			res += 1 << i;
		}
	}
	return sign == 1 ? res : -res;
}

//方法二：只允许使用 int
int divide2(int dividend, int divisor)
{
	//首先 需要判断边界条件
	if (dividend == INT_MIN && divisor == 1) return INT_MAX;
	if (dividend == 0) return 0;

	//其次，全部使用正数处理
	int flag = 1;
	if (dividend < 0)
	{
		dividend = -dividend;
		flag *= -1;
	}
	if (divisor < 0)
	{
		divisor = -divisor;
		flag *= -1;
	}

	//利用位运算处理两个正数相除
	int ans = 0;
	//从高位开始运算
	for (int i = 31; i >= 0; i--)
	{
		if ((dividend >> i) >= divisor)
		{
			ans += 1 << i;
			dividend -= (divisor << i);
		}
	}
	return ans * flag;

}

//题目三：实现快速乘
int QuickMulti(int a, int b)
{
	//a*b
	int ans = 0;
	int base = a;
	while (b)
	{
		if (b & 1) ans += a;
		a += a;
		b >>= 1;
	}
	return ans;
}

int AddToTarget(int target) 
{
	return QuickMulti(target + 1, target) / 2;
}

//题目四：实现快速幂  
double myQuickPow(double x, int n)
{
	double ans = 1;
	//根据n的正负 初始化不同的base值（x 或者 1/x）
	double base = n >= 0 ? x : 1 / x;
	while (n != 0)
	{
		if (n & 1) ans *= base;    //ans 需要 *=base
		base *= base;
		n >>= 1;
	}
	return ans;
}