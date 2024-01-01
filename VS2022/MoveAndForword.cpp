#include <type_traits>


//move����ʵ�֣�ǿ��ת������ֵ����
template<typename T>
typename std::remove_reference<T>::type&& myMove(T&& t)
{
	return static_cast<typename std::remove_reference<T>::type&&>(t);
}


//forward����ʵ�֣����ֲ��������Ͳ���
template<typename T>
T&& myForward(typename std::remove_reference<T>::type& t) 
{
	return static_cast<T&&>(t);
}