#include<vector>
#include <iostream>
using namespace std;

//题目一：数组中：只有一个数出现了1次，其他数均出现了两次
int singleNumber1(vector<int>& nums)
{
	int eor = 0;
	//eor异或上数组中每一个数 最后得到既答案a
	for (int i = 0; i < nums.size(); i++)
	{
		eor ^= nums[i];
	}
	return eor;
}


//题目二：数组中：只有两个数出现了1次，其他数均出现了两次
vector<int> singleNumber2(vector<int>& nums)
{
	int eor = 0;
	//eor异或上数组中每一个数 最后 eor=a^b
	for (int i = 0; i < nums.size(); i++)
	{
		eor ^= nums[i];
	}
	//获取eor最右边的1 ， 由于a!=b 所以可以根据rightMostOne区分成两种数
	int rightMostOne = eor & (~eor + 1);//或者 eor&(-eor)  注意数据可能会溢出
	int eor2 = 0;
	for (int i = 0; i < nums.size(); i++)
	{
		if ((nums[i] & rightMostOne) != 0) eor2 ^= nums[i];
	}
	eor ^= eor2;
	return { eor,eor2 };
}



//题目三：数组中：只有一个数出现了1次，其他数均出现了三次
int singleNumber3_1(vector<int>& nums)
{
	int bit[32] = { 0 };  //统计每一位上1出现的个数
	for (int i = 0; i < nums.size(); i++)
	{
		int count = 0;
		unsigned int t = nums[i]; //用无符号数处理负数出错问题：-1右移1位还是-1
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
		if (bit[i] % 3 == 1) //1出现的个数不是3的倍数，说明ans在此位上是1
			ans += (1 << i); //+= |= 一样
	}
	return ans;
}

//另一种写法：依次确定32位
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
			ans += (1 << i);//+= |= 一样
		}
	}
	return ans;
}

//题目四：数组中：只有两个数出现了1次，其他数均出现了三次
vector<int> singleNumber4(vector<int>& nums) 
{
	int bit[32] = { 0 };  //统计每一位上1出现的个数
	for (int i = 0; i < nums.size(); i++)
	{
		int count = 0;
		unsigned int t = nums[i]; //用无符号数处理负数出错问题
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
	//同样可以根据划分 调用题目三 得到结果
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
			ans1 += (1 << i);//+= |= 一样
		}
	}
	eor ^= ans1;
	return { ans1,eor };
}
