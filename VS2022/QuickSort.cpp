#include<vector>
#include<ctime>
using namespace std;
//快速排序

//划分过程
int Partition1(vector<int>& arr, int l, int r)
{
	int x = arr[l];
	int i = l, j = r;
	while (1)
	{
		while (i <= j && arr[i] <= x) i++;
		while (arr[j] > x) j--;
		if (i >= j) break;
		swap(arr[i], arr[j]);
	}
	swap(arr[l], arr[j]);
	return j;
}

//采用荷兰国旗的思路求解
pair<int, int> Partition2(vector<int>& arr, int l, int r)
{
	int less = l - 1; //小于区域
	int more = r + 1; //大于区域
	int pivot = arr[l]; //定义基准值
	int i = l + 1;
	while (i < more)
	{
		if (arr[i] < pivot)  swap(arr[++less], arr[i++]);
		else if (arr[i] > pivot) swap(arr[--more], arr[i]);
		else  i++;
	}
	return { less,more };
}

int partition3(int arr[], int l, int r)
{
	int pivot = arr[l];  // 取第一个元素作为基准值（pivot）
	int i = l + 1;       // 初始化i，指向pivot后的第一个元素

	for (int j = l + 1; j <= r; j++)
	{
		if (arr[j] < pivot)
		{   // 如果当前元素小于基准值
			swap(arr[i], arr[j]);// 将当前元素与前面的大于基准值的元素交换位置，保证小于基准值的都在左边
			i++;                // 增加小于基准值元素的索引位置
		}
	}
	swap(arr[l], arr[i - 1]);   // 把基准值放到正确的位置上，此时，左侧所有数都比它小，右侧所有数都比它大
	return (i - 1);
}

//递归过程
void QuickSort(vector<int>& arr, int l, int r)
{
	if (l >= r) return;
	pair<int, int> p = Partition2(arr, l, r);
	QuickSort(arr, l, p.first);
	QuickSort(arr, p.second, r);
}

void RandomQuickSort(vector<int>& arr, int l, int r)
{
	if (l >= r) return;
	srand(time(0));
	swap(arr[l], arr[rand() % (r - l + 1) + l]);
	pair<int, int> p = Partition2(arr, l, r);
	QuickSort(arr, l, p.first);
	QuickSort(arr, p.second, r);
}

//求最小的k个数
//方法一：基于堆
//方法二：基于快速排序
class Solution {
public:

	vector<int> ans;
	int Partition1(vector<int>& arr, int l, int r)
	{
		int x = arr[l];
		int i = l, j = r;
		while (1)
		{
			while (i <= j && arr[i] <= x) i++;
			while (arr[j] > x) j--;
			if (i >= j) break;
			swap(arr[i], arr[j]);
		}
		swap(arr[l], arr[j]);
		return j;
	}


	void QuickSort(vector<int>& arr, int l, int r, int k)
	{
		if (l >= r) return;
		srand(time(0));
		swap(arr[l], arr[rand() % (r - l + 1) + l]);
		int p = Partition1(arr, l, r);
	}

	//基于快速排序来实现
	vector<int> getLeastNumbers(vector<int>& arr, int k)
	{


	}
};