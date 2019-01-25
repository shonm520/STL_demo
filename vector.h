#pragma once
//#include "simple_alloc.h"
#include "alloc.h"
#include "construct.h"


namespace TinySTL  
{
	template<typename T, typename TAlloc = Alloc>
	class MyVector
	{
	public:
		typedef T value_type;
		typedef size_t size_type;
		typedef value_type* pointer;
		typedef value_type* iterator;
		typedef value_type& reference;

	protected:
		typedef SimpleAlloc<value_type, TAlloc> data_allocator;
		iterator start;
		iterator finish;
		iterator end_of_storage;

		iterator allocate_and_fill(size_type n, const T& val)  {
			iterator result = data_allocator::allocate(n);
			uninitialized_fill_n(result, n, val);
			return result;
		}

		void fill_initialize(size_type n, const value_type& value)  {
			start = Alloc::allocate(2 * n);
			uninitialized_fill_n(start, n, value);
			finish = start + n;
			end_of_storage = start + 2 * n;
		}

		void deallocate()  {
			if (start)  {
				data_allocator::deallocate(start, end_of_storage - start);
			}
		}

		void insert_aux(iterator pos, const T& value);

	public:
		MyVector(): start(0), finish(0), end_of_storage(0) {}

		MyVector(size_type n, const T& value)  {
			fill_initialize(n, value);
		}

		explicit MyVector(size_type n)  {
			fill_initialize(n, value_type());
		}

		~MyVector()  {
			destroy(start, finish);
			deallocate();
		}

		//iterator

		iterator begin()  {return start;}
		iterator end() {return finish;}
		size_type size() {return size_type(end() - begin());}
		bool empty()  {return size == 0;}
		size_type capacity()  {return size_type(end_of_storage - begin());}
		size_type max_size()  {return size_type(end_of_storage - begin());}
		
		//element access
		reference front()  {return *begin();}
		reference back()  {return *(end() - 1);}
		reference operator[](size_type idx)  {return *(begin() + idx);}
		reference at(size_type n)  {return *(begin() + n);}

		//modify
		void push_back(const T& val);
		void pop_back();

		//insert
		iterator insert(iterator pos, const T& val);
		iterator insert(iterator pos, size_type n, const T& val);

		

		//erase
		iterator erase(iterator pos)  {
			if (pos != end())  {
				copy(pos + 1, finish, pos);
			}
			--finish;
			destroy(finish);
			return pos;
		}

		iterator erase(iterator first, iterator last)  {
			iterator i = copy(last, finish, first);
			destroy(i, finish);
			finish = finish - (last - first);
			return first;
		}

		void clear()  {
			destroy(begin(), end());
			start = finish = end_of_storage = 0;
		}

		

	};

}

#include "vector_impl.h"