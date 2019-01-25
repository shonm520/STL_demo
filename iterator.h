#pragma once
#include <stddef.h>

namespace TinySTL  {


struct input_iterator_tag{};
struct output_iterator_tag{};
struct forward_iterator_tag : public input_iterator_tag{};
struct bidirectional_iterator_tag : public forward_iterator_tag{};
struct random_access_iterator_tag : public bidirectional_iterator_tag{};

template<typename Category, typename T,
		  typename Distance=ptrdiff_t,
		  typename Pointer=T*,
		  typename Reference = T&>
struct iterator  {
	typedef Category iterator_category;
	typedef T value_type;
	typedef Distance difference_type;
	typedef Pointer pointer;
	typedef Reference reference;
};


template<typename Iterator>
struct iterator_traits  {
	typedef typename Iterator::value_type value_type;
	typedef typename Iterator::difference_type difference_type;
	typedef typename Iterator::pointer pointer;
	typedef typename Iterator::reference reference;
	typedef typename Iterator::iterator_category iterator_category;
};

template<typename Iterator>
struct iterator_traits<Iterator*>  {
	typedef Iterator value_type;
	typedef ptrdiff_t difference_type;
	typedef Iterator* pointer;
	typedef Iterator& reference;
	typedef random_access_iterator_tag iterator_category;
};

template<typename Iterator>
struct iterator_traits<const Iterator*>  {
	typedef Iterator value_type;
	typedef ptrdiff_t difference_type;
	typedef const Iterator* pointer;
	typedef const Iterator& reference;
	typedef random_access_iterator_tag iterator_category;
};

template<typename Iterator>
typename iterator_traits<Iterator>::value_type*    //typename的意思是iterator_traits<Iterator>::value_type是个类型
value_type(const Iterator &)  {
	return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
}


}