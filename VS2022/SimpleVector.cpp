#include <algorithm> // std::copy, std::move
#include <stdexcept> // std::out_of_range

template<typename T>
class SimpleVector {
public:
	SimpleVector() : arr(nullptr), _size(0), _capacity(0) {}

	~SimpleVector() { delete[] arr; }

	// 移动构造函数
	SimpleVector(SimpleVector&& other) noexcept : _size(other._size), _capacity(other._capacity), arr(other.arr)
	{
		other._size = 0;
		other._capacity = 0;
		other.arr = nullptr;
	}

	// 移动赋值运算符
	SimpleVector& operator=(SimpleVector&& other) noexcept
	{
		if (this != &other) {
			delete[] arr;

			_size = other._size;
			_capacity = other._capacity;
			arr = other.arr;

			other._size = 0;
			other._capacity = 0;
			other.arr = nullptr;
		}

		return *this;
	}

	void push_back(const T& value) {
		if (_size == _capacity) {
			resize(std::max(1, 2 * _capacity));
		}
		arr[_size++] = value;
	}

	size_t size() const { return _size; }

	T& operator[](size_t index) {
		if (index >= _size) throw std::out_of_range("Index out of range");
		return arr[index];
	}

private:
	void resize(size_t new_capacity) {
		T* new_data = new T[new_capacity];

		if (arr != nullptr)
		{
			//
			std::copy(arr, arr + _size, new_data);
			delete[] arr;
		}

		arr = new_data;
		_capacity = new_capacity;
	}


private:
	T* arr;
	size_t _size;
	size_t _capacity;
};