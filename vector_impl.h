#pragma once
#include "algorithm.h"
#include "uninitialized.h"

namespace TinySTL  {

template<typename T, typename TAlloc>
void MyVector<T, TAlloc>::insert_aux(iterator pos, const T& value)  {
	if (finish != end_of_storage)  {
		construct(finish, *(finish - 1));
		++finish;
		copy_backward(pos, finish - 2, finish - 1);
		*pos = value;
	}
	else  {    //扩容或初始化
		const size_type old_size = size();
		const size_type new_size = (old_size == 0 ? 1 : 2 * old_size);
		iterator new_start = data_allocator::allocate(new_size);
		iterator new_finish = uninitialized_copy(start, pos, new_start);  //将start开始区域的对象复制到后面new_start
		construct(new_finish, value);
		++new_finish;
		uninitialized_copy(pos, finish, new_finish);    //将后面的对象也复制，只是从中间插入时才需要

		destroy(begin(), end());
		deallocate();
		start = new_start;
		finish = new_finish;
		end_of_storage = start + new_size;
	}
}

template<typename T, typename Alloc>
void MyVector<T, Alloc>::push_back(const T& val)  {
	if (finish != end_of_storage)  {    //还没有用尽空间
		construct(finish, val);
		++finish;
	}
	else  {
		insert_aux(end(), val);      //从尾部插入
	}
}

template<typename T, typename TAlloc>
void MyVector<T, TAlloc>::pop_back()  {
	--finish;
	destroy(finish);
}

}