#include<stdexcept>

//��̬����
template<typename T>
class SimpleVector
{
private:
	T* arr;
	size_t size;
	size_t capacity;

	//����
	void expansionCapacity(size_t new_capacity)
	{
		capacity = new_capacity;
		T* newArr = new T[capacity];
		//��Ԫ��ִ�и���/�ƶ�
		for (int i = 0; i < size; i++)
		{
			newArr[i] = arr[i];
			//newArr[i]=std::move(arr[i]);
		}
		delete[] arr;
		arr = newArr;
	}

public:
	//���캯�� ��������
	SimpleVector() : arr(nullptr), size(0), capacity(0) {}

	~SimpleVector() { delete[] arr; }

	//���ƹ��캯�� ��ֵ�����
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

	//�ƶ����캯�� �ƶ���ֵ�����
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

	//swap����
	void swap(SimpleVector& other)
	{
		if (this == &other) return;

		std::swap(arr, other.arr);
		std::swap(size, other.size);
		std::swap(capacity, other.capacity);
	}

	//��ĩβ���Ԫ��
	void push_back(const T& value)
	{
		if (size == capacity)
		{
			expansionCapacity(2 * capacity);
		}
		arr[size++] = value;

	}

	//ȥ��ĩβԪ��
	void pop_back()
	{
		if (size == 0) return;
		size--;
	}

	//����[]�����
	T& operator[](size_t index) const
	{
		if (index >= size) throw std::out_of_range("Index out of range");
		return arr[index];
	}

	//resize��������ı��С
	void resize(size_t new_size, const T& value = T())
	{
		//new_size��ԭ����size��ҪС����Ҫɾ�������Ԫ��
		if (new_size < size)
		{
			while (size != new_size) pop_back();
		}
		//new_size��������Ҫ��  ��Ҫ����
		if (new_size > capacity)
		{
			expansionCapacity(new_size);
		}
		//new_size��ԭ����sizeҪ����Ҫ��ĩβ���Ԫ��
		if (new_size > size)
		{
			while (size != new_size) push_back(value);
		}

	}

	//reserve��������ı�����
	void reserve(size_t new_capacity)
	{
		//�������Ⱦ�������ҪС ��ִ���κβ���
		if (new_capacity < capacity) return;

		//ֱ��������������
		expansionCapacity(new_capacity);
	}


	//����������Ԫ�ص�����
	size_t getSize() const { return size; }

	//�п�
	bool empty() const { return size == 0; }

};
