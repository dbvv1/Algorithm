#include<stdexcept>

//双向链表
template<typename T>
class SimpleList 
{
private:
	class ListNode
	{
	public:
		T m_value;
		ListNode* pre;
		ListNode* next;
		ListNode() :pre(nullptr), next(nullptr) {}
		ListNode(const T& value) :m_value(value), pre(nullptr), next(nullptr) {}
	};
	ListNode* head;
	ListNode* tail;
	size_t size;

public:
	//构造函数 析构函数
	SimpleList() :head(nullptr), tail(nullptr), size(0) {}

	~SimpleList() 
	{
		ListNode* p = head;
		while (p)
		{
			ListNode* t = p->next;
			delete(p);
			p = t;
		}
	}

	//复制构造函数 赋值运算符
	SimpleList(const SimpleList& other) :size(other.size)
	{
		ListNode* p = other.head;
		ListNode* hair = new ListNode();
		ListNode* t = hair;
		while (p)
		{
			t->next = new ListNode(p->m_value);
			t->next->pre = t;
			t = t->next;
			p = p->next;
		}
		head = hair->next;
		tail = t;
		tail->next = nullptr;
		delete(hair);
	}

	SimpleList& operator=(const SimpleList& other)
	{
		if (head == other.head)  return *this;
		size = other.size;
		ListNode* p = other.head;
		ListNode* hair = new ListNode();
		ListNode* t = hair;
		while (p)
		{
			t->next = new ListNode(p->m_value);
			t->next->pre = t;
			t = t->next;
			p = p->next;
		}
		head = hair->next;
		tail = t;
		tail->next = nullptr;
		delete(hair);

		return *this;
	}

	void push_front(const T& value)
	{
		ListNode* new_head = new ListNode(value);
		if (!empty())
		{
			new_head->next = head;
			head->pre = new_head;
			head = new_head;
		}
		else
		{
			head = tail = new_head;
		}
		size++;
	}

	void push_back(const T& value)
	{
		ListNode* new_tail = new ListNode(value);
		if (!empty())
		{
			tail->next = new_tail;
			new_tail->pre = tail;
			tail = new_tail;
		}
		else
		{
			head = tail = new_tail;
		}
		size++;
	}

	T& pop_front()
	{
		if (empty()) throw std::out_of_range("List is empty");
		ListNode* new_head = head->next;
		T& res = head->m_value;
		delete(head);
		head = new_head;
		size--;
		return res;

	}

	T& pop_back()
	{
		if (empty()) throw std::out_of_range("List is empty");
		ListNode* new_tail = tail->pre;
		T& res = tail->m_value;
		delete(tail);
		tail = new_tail;
		size--;
		return T;
	}

	void insert(const ListNode* place,const T& value)
	{
		if (place == nullptr) return;
		ListNode* p = new ListNode(value);
		place->pre = p;
		p->next = place;
		size++;
	}

	void erase(const ListNode* place)
	{
		if (place == nullptr) return;
		place->pre->next = place->next;
		place->next->pre = place->pre;
		size--;
		delete(place);
	}

	size_t getSize() const { return size; }

	bool empty() const { return size == 0; }

};