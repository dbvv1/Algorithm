#include<vector>
#include <iostream>
using namespace std;

//��Ŀһ�������У�ֻ��һ����������1�Σ�������������������
int singleNumber1(vector<int>& nums)
{
	int eor = 0;
	//eor�����������ÿһ���� ���õ��ȴ�a
	for (int i = 0; i < nums.size(); i++)
	{
		eor ^= nums[i];
	}
	return eor;
}


//��Ŀ���������У�ֻ��������������1�Σ�������������������
vector<int> singleNumber2(vector<int>& nums)
{
	int eor = 0;
	//eor�����������ÿһ���� ��� eor=a^b
	for (int i = 0; i < nums.size(); i++)
	{
		eor ^= nums[i];
	}
	//��ȡeor���ұߵ�1 �� ����a!=b ���Կ��Ը���rightMostOne���ֳ�������
	int rightMostOne = eor & (~eor + 1);//���� eor&(-eor)  ע�����ݿ��ܻ����
	int eor2 = 0;
	for (int i = 0; i < nums.size(); i++)
	{
		if ((nums[i] & rightMostOne) != 0) eor2 ^= nums[i];
	}
	eor ^= eor2;
	return { eor,eor2 };
}



//��Ŀ���������У�ֻ��һ����������1�Σ�������������������
int singleNumber3_1(vector<int>& nums)
{
	int bit[32] = { 0 };  //ͳ��ÿһλ��1���ֵĸ���
	for (int i = 0; i < nums.size(); i++)
	{
		int count = 0;
		unsigned int t = nums[i]; //���޷������������������⣺-1����1λ����-1
		while (t)
		{
			if (t & 1) bit[count]++;
			count++;
			t >>= 1;
		}
	}
	int ans = 0;
	for (int i = 0; i < 32; i++)
	{
		if (bit[i] % 3 == 1) //1���ֵĸ�������3�ı�����˵��ans�ڴ�λ����1
			ans += (1 << i); //+= |= һ��
	}
	return ans;
}

//��һ��д��������ȷ��32λ
int singleNumber3_2(vector<int>& nums) {
	int ans = 0;
	for (int i = 0; i < 32; ++i)
	{
		int total = 0;
		for (int num : nums)
		{
			total += ((num >> i) & 1);
		}
		if (total % 3)
		{
			ans += (1 << i);//+= |= һ��
		}
	}
	return ans;
}

//��Ŀ�ģ������У�ֻ��������������1�Σ�������������������
vector<int> singleNumber4(vector<int>& nums) 
{
	int bit[32] = { 0 };  //ͳ��ÿһλ��1���ֵĸ���
	for (int i = 0; i < nums.size(); i++)
	{
		int count = 0;
		unsigned int t = nums[i]; //���޷�������������������
		while (t)
		{
			if (t & 1) bit[count]++;
			count++;
			t >>= 1;
		}
	}
	//eor=a^b
	int eor = 0;
	for (int i = 0; i < 32; i++)
	{
		if (bit[i] % 3 == 1) eor += 1 << i;
	}
	//ͬ�����Ը��ݻ��� ������Ŀ�� �õ����
	int rightMostOne = eor & (-eor);
	int ans1 = 0;
	for (int i = 0; i < 32; ++i)
	{
		int total = 0;
		for (int num : nums)
		{
			if ((num & rightMostOne) != 0)
				total += ((num >> i) & 1);
		}
		if (total % 3)
		{
			ans1 += (1 << i);//+= |= һ��
		}
	}
	eor ^= ans1;
	return { ans1,eor };
}
