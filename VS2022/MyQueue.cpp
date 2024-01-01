#include<deque>
#include<stdexcept>
template<typename T>
class MyQueue
{
private:
	std::deque<T> q;

public:
	void push(const T& value) 
	{
		q.push_back(value);
	}

	T& pop()
	{
		if (empty()) throw std::out_of_range("Stack is empty");
		T& res = q.front();
		q.pop_front();
		return res;
	}

	T& front()
	{
		if (empty()) throw std::out_of_range("Stack is empty");
		return q.front();
	}

	size_t getSize() const { return q.size(); }

	bool empty() const { return q.size() == 0; }
	
};