#pragma once 

#include <memory>
#include <new>
#include "alloc.h"
using namespace std;

namespace TinySTL
{
	template <class T>
	class SimpleAllocate  
	{
	public:
		typedef T value_type;
		typedef size_t size_type;
		typedef value_type* value_ptr;
		static TinySTL::Alloc alloc;

		static value_ptr allocate(size_type n)  {
			return static_cast<value_ptr>(Alloc::allocate(n * sizeof(value_type)));
		}

		static void deallocate(value_ptr p, size_type n)  {
			Alloc::deallocate(p, n * sizeof(value_type));
		}

		static void construct(value_ptr p, const value_type& value)  {
			new (p) value_type(value);
		}

		static void destroy(value_ptr p)  {
			p->~T();
		}
	};

	template<class T>
	TinySTL::Alloc SimpleAllocate<T>::alloc;// = allocator<T>();
}