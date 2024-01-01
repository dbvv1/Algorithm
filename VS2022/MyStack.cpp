#include<deque>
#include<stdexcept>
template<typename T>
class MyStack
{
private:
	std::deque<T> s;


public:
	void push(const T& value)
	{
		s.push_back(value);
	}

	T& pop()
	{
		if(empty()) throw std::out_of_range("Stack is empty");
		T& res = s[s.size() - 1];
		s.pop_back();
		return res;
	}

	T& top()
	{
		if (empty()) throw std::out_of_range("Stack is empty");
		
		return s[s.size() - 1];
	}

	size_t getSize() const { return s.size(); }
	
	bool empty() const { return s.size()==0; }
};