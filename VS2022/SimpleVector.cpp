#include<stdexcept>

//动态数组
template<typename T>
class SimpleVector
{
private:
	T* arr;
	size_t size;
	size_t capacity;

	//扩容
	void expansionCapacity(size_t new_capacity)
	{
		capacity = new_capacity;
		T* newArr = new T[capacity];
		//逐元素执行复制/移动
		for (int i = 0; i < size; i++)
		{
			newArr[i] = arr[i];
			//newArr[i]=std::move(arr[i]);
		}
		delete[] arr;
		arr = newArr;
	}

public:
	//构造函数 析构函数
	SimpleVector() : arr(nullptr), size(0), capacity(0) {}

	~SimpleVector() { delete[] arr; }

	//复制构造函数 赋值运算符
	SimpleVector(const SimpleVector& other) :size(other.size), capacity(other.capacity)
	{
		arr = new T[capacity];
		for (int i = 0; i < size; i++)
		{
			arr[i] = other.arr[i];
		}
	}

	SimpleVector& operator=(const SimpleVector& other) 
	{
		if (this == &other) return *this;
		delete[] arr;
		size = other.size;
		capacity = other.capacity;
		arr = new T[capacity];
		for (int i = 0; i < size; i++)
		{
			arr[i] = other.arr[i];
		}

		return *this;

	}

	//移动构造函数 移动赋值运算符
	SimpleVector(const SimpleVector&& other) noexcept :arr(other.arr), size(other.size), capacity(other.capacity)
	{
		other.arr = nullptr;
		other.size = 0;
		other.capacity = 0;
	}

	SimpleVector& operator=(const SimpleVector&& other) noexcept 
	{
		if (this == &other) return *this;

		arr = other.arr;
		size = other.size;
		capacity = other.capacity; 

		other.arr = nullptr;
		other.size = 0;
		other.capacity = 0;

		return *this;
	}

	//swap操作
	void swap(SimpleVector& other)
	{
		if (this == &other) return;

		std::swap(arr, other.arr);
		std::swap(size, other.size);
		std::swap(capacity, other.capacity);
	}

	//向末尾添加元素
	void push_back(const T& value)
	{
		if (size == capacity)
		{
			expansionCapacity(2 * capacity);
		}
		arr[size++] = value;

	}

	//去除末尾元素
	void pop_back()
	{
		if (size == 0) return;
		size--;
	}

	//重载[]运算符
	T& operator[](size_t index) const
	{
		if (index >= size) throw std::out_of_range("Index out of range");
		return arr[index];
	}

	//resize函数：会改变大小
	void resize(size_t new_size, const T& value = T())
	{
		//new_size比原来的size还要小，需要删除多余的元素
		if (new_size < size)
		{
			while (size != new_size) pop_back();
		}
		//new_size比容量还要大  需要扩容
		if (new_size > capacity)
		{
			expansionCapacity(new_size);
		}
		//new_size比原来的size要大，需要向末尾添加元素
		if (new_size > size)
		{
			while (size != new_size) push_back(value);
		}

	}

	//reserve函数：会改变容量
	void reserve(size_t new_capacity)
	{
		//新容量比旧容量还要小 不执行任何操作
		if (new_capacity < capacity) return;

		//直接扩容容量即可
		expansionCapacity(new_capacity);
	}


	//返回数组中元素的数量
	size_t getSize() const { return size; }

	//判空
	bool empty() const { return size == 0; }

};
