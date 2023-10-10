#include<vector>
using namespace std;

//ʵ�ֶ�
template<typename T, typename Compare = std::less<T>>
class MyPriorityQueue
{
private:
	vector<T> arr;
	Compare comp;
	//���������(���ӷ�Ҷ�ӽ�㿪ʼ���µ���)
	void Heapify()
	{
		for (int i = (arr.size() - 2) / 2; i >= 0; i--)
		{
			PushDown(i);
		}
	}

	//��xλ�ÿ�ʼ���µ���
	void PushDown(int x)
	{
		int cur = x;
		while (cur * 2 + 1 < arr.size())
		{
			int left = cur * 2 + 1;
			int right = cur * 2 + 2;
			int choose = right == arr.size() ? left : (comp(arr[left], arr[right]) ? right : left);
			if (!comp(arr[cur], arr[choose])) break;
			swap(arr[cur], arr[choose]);
			cur = choose;
		}
	}

	//��xλ�ÿ�ʼ���ϵ���
	void PushUp(int x)
	{
		int cur = x;
		while ((cur - 1) / 2 >= 0)
		{
			int father = (cur - 1) / 2;
			if (comp(arr[cur], arr[father])) break;
			swap(arr[cur], arr[father]);
			cur = father;
		}
	}



public:
	MyPriorityQueue() {}
	MyPriorityQueue(const vector<int>& a) : arr(a)
	{
		Heapify();
	}

	//���ضѶ�Ԫ��
	T Top()
	{
		if (arr.size() == 0) return INT_MIN;
		return arr[0];
	}

	//ɾ���Ѷ�Ԫ�� ������
	T Pop()
	{
		//����Ԫ����βԪ�ؽ��� ��ִ��PushDown����
		T res = arr[0];
		swap(arr[0], arr[arr.size() - 1]);
		arr.pop_back();
		PushDown(0);
		return res;
	}

	//���������Ԫ��x
	void Push(int x)
	{
		//��arrĩβ���Ԫ�� ����ִ��PushUp����
		arr.push_back(x);
		PushUp(arr.size() - 1);
	}

	//���ضѵĴ�С
	int Size()
	{
		return arr.size();
	}

	bool Empty()
	{
		return arr.empty();
	}

};
