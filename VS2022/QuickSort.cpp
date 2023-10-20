#include<vector>
#include<ctime>
using namespace std;
//��������

//���ֹ���
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

//���ú��������˼·���
pair<int, int> Partition2(vector<int>& arr, int l, int r)
{
	int less = l - 1; //С������
	int more = r + 1; //��������
	int pivot = arr[l]; //�����׼ֵ
	int i = l + 1;
	while (i < more)
	{
		if (arr[i] < pivot)  swap(arr[++less], arr[i++]);
		else if (arr[i] > pivot) swap(arr[--more], arr[i]);
		else  i++;
	}
	return { less + 1,more - 1 };
}

int partition3(int arr[], int l, int r)
{
	int pivot = arr[l];  // ȡ��һ��Ԫ����Ϊ��׼ֵ��pivot��
	int i = l + 1;       // ��ʼ��i��ָ��pivot��ĵ�һ��Ԫ��

	for (int j = l + 1; j <= r; j++)
	{
		if (arr[j] < pivot)
		{   // �����ǰԪ��С�ڻ�׼ֵ
			swap(arr[i], arr[j]);// ����ǰԪ����ǰ��Ĵ��ڻ�׼ֵ��Ԫ�ؽ���λ�ã���֤С�ڻ�׼ֵ�Ķ������
			i++;                // ����С�ڻ�׼ֵԪ�ص�����λ��
		}
	}
	swap(arr[l], arr[i - 1]);   // �ѻ�׼ֵ�ŵ���ȷ��λ���ϣ���ʱ�����������������С���Ҳ���������������
	return (i - 1);
}

//�ݹ����
void QuickSort(vector<int>& arr, int l, int r)
{
	if (l >= r) return;
	pair<int, int> p = Partition2(arr, l, r);
	QuickSort(arr, l, p.first - 1);
	QuickSort(arr, p.second + 1, r);
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

//����С��k����
//����һ�����ڶ�
//�����������ڿ�����������С�ĵ�k��������
class GetLeastNumbers {
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


	int QuickSort(vector<int>& arr, int l, int r, int k)
	{
		if (l >= r) return -1;
		srand(time(0));
		swap(arr[l], arr[rand() % (r - l + 1) + l]);
		int p = Partition1(arr, l, r);
		if (p - l + 1 == k) return p;
		else if (p - l + 1 > k) return QuickSort(arr, l, p - 1, k);
		else return QuickSort(arr, p + 1, r, k - (p - l + 1));
	}

	//���ڿ���������ʵ��
	vector<int> getLeastNumbers(vector<int>& arr, int k)
	{
		int p = QuickSort(arr, 0, arr.size() - 1, k);
		arr.resize(k);
		return arr;

	}
};

//�����ĵ�k����--����С�ĵ�n-k+1����
class FindKthLargest {
public:

	pair<int,int> Partition1(vector<int>& arr, int l, int r)
	{
		int less = l - 1; //С������
		int more = r + 1; //��������
		int pivot = arr[l]; //�����׼ֵ
		int i = l + 1;
		while (i < more)
		{
			if (arr[i] < pivot)  swap(arr[++less], arr[i++]);
			else if (arr[i] > pivot) swap(arr[--more], arr[i]);
			else  i++;
		}
		return { less + 1,more - 1 };
	}

	//����С�ĵ�k����
	int QuickSort(vector<int>& arr, int l, int r, int k)
	{
		if (l >= r) return l;
		srand(time(0));
		swap(arr[l], arr[rand() % (r - l + 1) + l]);
		pair<int, int> p = Partition1(arr, l, r);
		if (p.first - l + 1 <= k && p.second - l + 1 >= k) return p.first;
		else if (p.first - l + 1 > k) return QuickSort(arr, l, p.first - 1, k);
		else return QuickSort(arr, p.second + 1, r, k - (p.second - l + 1));
	}

	//���ڿ���������ʵ��
	int findKthLargest(vector<int>& nums, int k)
	{
		//1 2 3 4 5 ����ȫ1
		int p = QuickSort(nums, 0, nums.size() - 1, nums.size() - k + 1);
		return nums[p];

	}
};