
#include <bits/stdc++.h>
#include<random>
using namespace std;

//一副牌 能否全部由顺子打完
//方法一：暴力递归

class MyClass
{
public:
	string m_name;
	int m_number;

	//构造函数
	MyClass() :m_name(""), m_number(0)
	{
		cout << "默认构造函数" << endl;
	}
	MyClass(const string& name, const int number) :m_name(name), m_number(number)
	{
		cout << "带参构造函数" << endl;
	}

	//拷贝构造 重载赋值 =
	MyClass(const MyClass& other) :m_name(other.m_name), m_number(other.m_number)
	{
		cout << "复制构造函数" << endl;
	}

	MyClass& operator=(const MyClass& other)
	{
		cout << "复制赋值运算符" << endl;
		if (this != &other)
		{
			m_name = other.m_name;
			m_number = other.m_number;
		}
		return*this;
	}

	//移动构造 重载移动 =
	MyClass(MyClass&& other) noexcept :m_name(std::move(other.m_name)), m_number(other.m_number)
	{
		cout << "移动构造函数" << endl;
		other.m_number = 0;
	}

	MyClass& operator=(MyClass&& other) noexcept
	{
		cout << "移动赋值运算符" << endl;
		if (this != &other)
		{
			m_name = std::move(other.m_name);
			m_number = other.m_number;

			other.m_number = 0;
		}
		return *this;
	}


	~MyClass()
	{
		cout << "析构函数调用" << endl;
	}

};


class Base {
public:
	virtual void show() {
		cout << "Base::show()" << endl;
	}
};

class Derived : public Base {
	//没有声明新的虚函数，也没有重写父类的虚函数
};

//int main() {
//	Base b;
//	Derived d;
//
//	//获取虚函数表地址
//	//&b会取到Base对象的地址   (void***)vptr虚函数指针 指向虚函数表  对其解引用得到 void** 虚函数表指针 
//
//	void** vptr_base = *(void***)&b;
//	void** vptr_derived = *(void***)&d;
//	cout << "vptr_base address: " << vptr_base << endl;
//	cout << "vptr_derived address: " << vptr_derived << endl;        
//
//
//	void* vptr_base1 = *(void**)&b;
//	void* vptr_derived1 = *(void**)&d;
//
//	//打印虚函数表地址
//	cout << "vptr_base address: " << vptr_base1 << endl;
//	cout << "vptr_derived address: " << vptr_derived1 << endl;
//
//	return 0;
//}
//

