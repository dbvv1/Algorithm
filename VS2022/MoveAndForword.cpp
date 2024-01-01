#include <type_traits>


//move函数实现：强制转换成右值引用
template<typename T>
typename std::remove_reference<T>::type&& myMove(T&& t)
{
	return static_cast<typename std::remove_reference<T>::type&&>(t);
}


//forward函数实现：保持参数的类型不变
template<typename T>
T&& myForward(typename std::remove_reference<T>::type& t) 
{
	return static_cast<T&&>(t);
}