#pragma once



#include <string.h> //for memmove

namespace TinySTL
{

template<typename InputIterator,typename OutputIterator>
OutputIterator __uninitialized_copy_aux(InputIterator first, InputIterator last, OutputIterator result, __true_type)
{
	//FIXME 之后实现了copy算法后应该使用copy算法
	while(first != last)  {
		*result = *first;
		++first;
		++result;
	}
	return result;
}

template<typename InputIterator, typename OutputIterator>
OutputIterator __uninitialized_copy_aux(InputIterator first, InputIterator last, OutputIterator result, __false_type)
{
	while(first != last)  {
		construct(&*result, *first);
		++first;
		++result;
	}
	return result;
}

template<typename InputIterator, typename OutputIterator, typename T>
OutputIterator __uninitialized_copy(InputIterator first, InputIterator last, OutputIterator result, T*)
{
	typedef typename __type_traits<T>::is_POD_type is_POD;
	return __uninitialized_copy_aux(first, last, result, is_POD());
}


template<typename InputIterator, typename OutputIterator>
OutputIterator uninitialized_copy(InputIterator first, InputIterator last, OutputIterator result)
{
	return __uninitialized_copy(first, last, result, value_type(result));
}

template<>
char* uninitialized_copy(const char* first, const char* last, char* result)
{
	size_t n = last - first;
	memmove(result, first, n);
	return result + n;
}

template<>
wchar_t* uninitialized_copy(const wchar_t* first, const wchar_t* last, wchar_t* result)
{
	size_t n = last - first;
	memmove(result, first, n * sizeof(wchar_t));
	return result + n;
}


template<typename InputIterator, typename T>
void __uninitialized_fill_aux(InputIterator first,InputIterator last,const T& value,__true_type)
{
	//FIXME 之后实现了fill算法后应该使用fill算法
	while(first!=last)
	{
		*first=value;
		++first;
	}

}

template<typename InputIterator,typename T>
void __uninitialized_fill_aux(InputIterator first,InputIterator last,const T& value,__false_type)
{
	while(first!=last)
	{
		construct(&*first,value);
		++first;
	}

}

template<typename InputIterator,typename T,typename U>
void __uninitialized_fill(InputIterator first,InputIterator last,const T& value,U*)
{
	typedef typename __type_traits<U>::is_POD_type is_POD;
	__uninitialized_fill_aux(first,last,value,is_POD());
}

template<typename InputIterator,typename T>
void uninitialized_fill(InputIterator first,InputIterator last,const T& value)
{
	__uninitialized_fill(first,last,value,value_type(first));
}

template<typename InputIterator,typename Size,typename T>
InputIterator __uninitialized_fill_n_aux(InputIterator first,Size n,const T& value,__false_type)
{
	InputIterator cur = first;
	for(;n>0;--n)
	{
		construct(&*cur,value);
		++cur;
	}
	return cur;

}

template<typename InputIterator,typename Size,typename T>
InputIterator __uninitialized_fill_n_aux(InputIterator first,Size n,const T& value,__true_type)
{
	//FIXME 之后实现了fill_n算法后应该使用fill_n算法
	InputIterator cur = first;
	for(;n>0;--n)
	{
		*cur = value;
		++cur;
	}
	return cur;

}

template<typename InputIterator,typename Size,typename T,typename U>
InputIterator __uninitialized_fill_n(InputIterator first,Size n,const T& value,U*)
{
	typedef typename __type_traits<U>::is_POD_type is_POD;
	return __uninitialized_fill_n_aux(first,n,value,is_POD());

}

template<typename InputIterator,typename Size,typename T>
InputIterator uninitialized_fill_n(InputIterator first,Size n,const T& value)
{
	return __uninitialized_fill_n(first,n,value,value_type(first));
}



}



