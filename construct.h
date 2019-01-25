#pragma once

#include <new>
#include "iterator.h"

namespace TinySTL  {

struct __true_type  {};
struct __false_type  {};

template<typename T>
struct __type_traits  {
	typedef __false_type has_trival_default_constructor;
	typedef __false_type has_trival_copy_constructor;
	typedef __false_type has_trival_assignment_constructor;
	typedef __false_type has_trival_destructor;
	typedef __false_type is_POD_type;
};

template<>
struct __type_traits<char>  {
	typedef __true_type  has_trival_default_constructor;
	typedef __true_type  has_trival_copy_constructor;
	typedef __true_type  has_trival_assignment_constructor;
	typedef __true_type  has_trival_destructor;
	typedef __true_type  is_POD_type;
};

template<typename T, typename V>
inline void construct(T* p, const V& value)  {
	new (p) V(value);
}

template<typename T>
inline void destroy(T* p)  {
	p->~T();
}

template<typename Iterator>
inline void __destroy_aux(Iterator first, Iterator last, __true_type)  {
	for(; first != last; ++first)  {
		destroy(&*first);
	}
}

template<typename Iterator>
inline void __destroy_aux(Iterator first, Iterator last, __false_type)  {

}

template <typename Iterator, typename T>
inline void __destroy(Iterator first, Iterator last, T*)  {
	typedef typename __type_traits<T>::has_trival_destructor trival_destructor;
	__destroy_aux(first, last, trival_destructor());
}

template<typename Iterator>
inline void destroy(Iterator first, Iterator last)  {
	__destroy(first, last, value_type(first));
}

}
