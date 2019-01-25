#ifndef __TINYSTL_ALGORITHM_HPP
#define __TINYSTL_ALGORITHM_HPP

#include <iostream>
#include <string.h>


//使用时候最好加上TinySTL::作用域

namespace TinySTL
{

template<typename RandomIterator,typename OutputIterator,typename Distance>
OutputIterator __copy_d(RandomIterator first,RandomIterator last,OutputIterator result,Distance*)
{
	std::cout<<"__copy_d  (RandomIterator first,RandomIterator last,OutputIterator result,Distance*)"<<std::endl;
	Distance n = last - first;
	for(;n>0;--n)
	{
		*result = *first;
		++result;
		++first;
	}
	return result;
}


template<typename T>
T* __copy_t(const T* first,const T* last,T* result,__false_type)
{
	std::cout<<"__copy_t  (const T* first,const T* last,T* result,__false_type)"<<std::endl;
	return __copy_d(first,last,result,(ptrdiff_t*)0);
}

template<typename T>
T* __copy_t(const T* first,const T* last,T* result,__true_type)
{
	std::cout<<"__copy_t (const T* first,const T* last,T* result,__true_type)"<<std::endl;
	memmove(result,first,(last-first)*sizeof(T));
	return result + (last - first);
}


template<typename InputIterator,typename OutputIterator>
OutputIterator __copy(InputIterator first,InputIterator last,OutputIterator result,input_iterator_tag)
{
	std::cout<<"__copy (InputIterator first,InputIterator last,OutputIterator result,input_iterator_tag)"<<std::endl;
	while(first!=last)
	{
		*result = *first;
		++first;
		++result;
	}
	return result;
}

template<typename RandomIterator,typename OutputIterator>
OutputIterator __copy(RandomIterator first,RandomIterator last,OutputIterator result,random_access_iterator_tag)
{
	std::cout<<"__copy (RandomIterator first,RandomIterator last,OutputIterator result,random_access_iterator_tag)"<<std::endl;
	return __copy_d(first,last,result,difference_type(first));
}


template<typename InputIterator,typename OutputIterator>
struct __copy_dispatch
{	
	
	OutputIterator operator()(InputIterator first,InputIterator last,OutputIterator result)
	{
		std::cout<<"struct __copy_dispatch"<<std::endl;
		return __copy(first,last,result,iterator_category(first));
	}
};

template<typename T>
struct __copy_dispatch<T*,T*>
{
	
	T* operator()(T* first,T* last,T* result)
	{
		std::cout<<"__copy_dispatch<T*,T*>"<<std::endl;
		typedef typename __type_traits<T>::has_trivial_assignment_operator has_trivial_assignment;
		return __copy_t(first,last,result,has_trivial_assignment());
	}
};

template<typename T>
struct __copy_dispatch<const T*,T*>
{
	
	T* operator()(const T* first,const T* last,T* result)
	{
		std::cout<<"__copy_dispatch<const T*,T*>"<<std::endl;
		typedef typename __type_traits<T>::has_trivial_assignment_operator has_trivial_assignment;
		return __copy_t(first,last,result,has_trivial_assignment());
	}
};

template<typename InputIterator,typename OutputIterator>
OutputIterator copy(InputIterator first,InputIterator last,OutputIterator result)
{
	std::cout<<"copy (InputIterator first,InputIterator last,OutputIterator result)"<<std::endl;
	return	__copy_dispatch<InputIterator,OutputIterator>()(first,last,result);
}

template<>
char* copy(const char* first,const char* last,char* result)
{
	std::cout<<"copy (const char* first,const char* last,char* result)"<<std::endl;
	memmove(result,first,(last-first)*sizeof(char));
	return result + (last - first);
}

template<>
wchar_t* copy(const wchar_t* first,const wchar_t* last,wchar_t* result)
{
	std::cout<<"copy (const wchar_t* first,const wchar_t* last,wchar_t* result)"<<std::endl;
	memmove(result,first,(last-first)*sizeof(wchar_t));
	return result + (last - first);
}

/*************************************************************************************************************************/

template<typename InputIterator,typename OutputIterator,typename Distance>
OutputIterator __copy_d_backward(InputIterator first,InputIterator last,OutputIterator result,Distance*)
{
	Distance n = last - first;
	for(;n>0;--n)
	{
		*(result-1) = *(last-1);
		--result;
		--last;
	}
	return result;
};


template<typename InputIterator,typename OutputIterator>
OutputIterator __copy_t_backward(InputIterator first,InputIterator last,OutputIterator result,input_iterator_tag)
{
	while(last!=first)
	{
		*(result-1) = *(last - 1);
		--last;
		--result;
	}
	return result;
};

template<typename InputIterator,typename OutputIterator>
OutputIterator __copy_t_backward(InputIterator first,InputIterator last,OutputIterator result,random_access_iterator_tag)
{
	return __copy_d_backward(first,last,result,difference_type(first));
};

template<typename InputIterator,typename OutputIterator>
struct __copy_dispatch_backward
{
	OutputIterator operator()(InputIterator first,InputIterator last,OutputIterator result)
	{
		return __copy_t_backward(first,last,result,iterator_category(first));
	}
};

template<typename T>
struct __copy_dispatch_backward<T*,T*>
{
	T* operator()(T* first,T* last,T* result)
	{
		return __copy_d_backward(first,last,result,(ptrdiff_t*)(0));
	}
};

template<typename T>
struct __copy_dispatch_backward<const T*,T*>
{
	T* operator()(const T* first,const T* last,T* result)
	{
		return __copy_d_backward(first,last,result,(ptrdiff_t*)(0));
	}
};

template<typename InputIterator,typename OutputIterator>
OutputIterator copy_backward(InputIterator first,InputIterator last,OutputIterator result)
{
	
	return	__copy_dispatch_backward<InputIterator,OutputIterator>()(first,last,result);
}

/************************************************************************************************************/

template<typename OutputIterator,typename T>
void fill(OutputIterator first,OutputIterator last,const T& value)
{
	for(;first!=last;++first)
		*first = value;
}

template<typename OutputIterator,typename Size,typename T>
OutputIterator fill_n(OutputIterator first,Size n,const T& value)
{
	for(;n>0;--n,++first)
		*first = value;
	return first;
}	

template<typename T>
T max(const T& a,const T& b)
{
	return a>b?a:b;
}


/************************************************************************************************************/

template<typename InputIterator,typename T>
InputIterator find(InputIterator first,InputIterator last,const T& value)
{
	while(first!=last && *first!=value) ++first;
	return first;
}

/************************************************************************************************************/
template<typename T>
void swap(T& a,T& b)
{
	T tmp = a;
	a = b;
	b = tmp;
}

}



#endif