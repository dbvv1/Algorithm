#include<vector>
using namespace std;

//实现堆
template<typename T, typename Compare = std::less<T>>
class MyPriorityQueue
{
private:
	vector<T> arr;
	Compare comp;
	//总体调整堆(即从非叶子结点开始向下调整)
	void Heapify()
	{
		for (int i = (arr.size() - 2) / 2; i >= 0; i--)
		{
			PushDown(i);
		}
	}

	//从x位置开始向下调整
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

	//向x位置开始向上调整
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

	//返回堆顶元素
	T Top()
	{
		if (arr.size() == 0) return INT_MIN;
		return arr[0];
	}

	//删除堆顶元素 并返回
	T Pop()
	{
		//将首元素与尾元素交换 并执行PushDown方法
		T res = arr[0];
		swap(arr[0], arr[arr.size() - 1]);
		arr.pop_back();
		PushDown(0);
		return res;
	}

	//往堆中添加元素x
	void Push(int x)
	{
		//在arr末尾添加元素 并且执行PushUp方法
		arr.push_back(x);
		PushUp(arr.size() - 1);
	}

	//返回堆的大小
	int Size()
	{
		return arr.size();
	}

	bool Empty()
	{
		return arr.empty();
	}

};
