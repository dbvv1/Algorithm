#include <climits>
#include <stdlib.h>

//��Ŀһ������ + ʵ�� �ӷ�
int add(int a, int b) {
	while (b != 0) {
		int carry = (unsigned int)(a & b) << 1; // �����λ
		a = a ^ b; // �����޽�λ�ӷ����
		b = carry; // ����λ��ֵ��b������һ��ѭ������a���
	}
	return a;
}

//��Ŀ�������� / ʵ�� ����
//����һ������ʹ���޷������� unsigned int
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

//��������ֻ����ʹ�� int
int divide2(int dividend, int divisor)
{
	//���� ��Ҫ�жϱ߽�����
	if (dividend == INT_MIN && divisor == 1) return INT_MAX;
	if (dividend == 0) return 0;

	//��Σ�ȫ��ʹ����������
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

	//����λ���㴦�������������
	int ans = 0;
	//�Ӹ�λ��ʼ����
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

//��Ŀ����ʵ�ֿ��ٳ�
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

//��Ŀ�ģ�ʵ�ֿ�����  
double myQuickPow(double x, int n)
{
	double ans = 1;
	//����n������ ��ʼ����ͬ��baseֵ��x ���� 1/x��
	double base = n >= 0 ? x : 1 / x;
	while (n != 0)
	{
		if (n & 1) ans *= base;    //ans ��Ҫ *=base
		base *= base;
		n >>= 1;
	}
	return ans;
}