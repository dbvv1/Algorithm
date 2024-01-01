
#include <bits/stdc++.h>
#include<random>
using namespace std;

//һ���� �ܷ�ȫ����˳�Ӵ���
//����һ�������ݹ�

class MyClass
{
public:
	string m_name;
	int m_number;

	//���캯��
	MyClass() :m_name(""), m_number(0)
	{
		cout << "Ĭ�Ϲ��캯��" << endl;
	}
	MyClass(const string& name, const int number) :m_name(name), m_number(number)
	{
		cout << "���ι��캯��" << endl;
	}

	//�������� ���ظ�ֵ =
	MyClass(const MyClass& other) :m_name(other.m_name), m_number(other.m_number)
	{
		cout << "���ƹ��캯��" << endl;
	}

	MyClass& operator=(const MyClass& other)
	{
		cout << "���Ƹ�ֵ�����" << endl;
		if (this != &other)
		{
			m_name = other.m_name;
			m_number = other.m_number;
		}
		return*this;
	}

	//�ƶ����� �����ƶ� =
	MyClass(MyClass&& other) noexcept :m_name(std::move(other.m_name)), m_number(other.m_number)
	{
		cout << "�ƶ����캯��" << endl;
		other.m_number = 0;
	}

	MyClass& operator=(MyClass&& other) noexcept
	{
		cout << "�ƶ���ֵ�����" << endl;
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
		cout << "������������" << endl;
	}

};


class Base {
public:
	virtual void show() {
		cout << "Base::show()" << endl;
	}
};

class Derived : public Base {
	//û�������µ��麯����Ҳû����д������麯��
};

//int main() {
//	Base b;
//	Derived d;
//
//	//��ȡ�麯�����ַ
//	//&b��ȡ��Base����ĵ�ַ   (void***)vptr�麯��ָ�� ָ���麯����  ��������õõ� void** �麯����ָ�� 
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
//	//��ӡ�麯�����ַ
//	cout << "vptr_base address: " << vptr_base1 << endl;
//	cout << "vptr_derived address: " << vptr_derived1 << endl;
//
//	return 0;
//}
//

