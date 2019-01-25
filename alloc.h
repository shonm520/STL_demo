#pragma once 
#include <stdlib.h>
namespace TinySTL  {

	class __alloc_bigsize
	{
	private:
		static void* oom_malloc(size_t);
		static void* oom_realloc(void*, size_t);
		static void (*__malloc_alloc_oom_handler)();

	public:
		static void* allocate(size_t n)  {
			void* res = malloc(n);
			if(0 == res) res = oom_malloc(n);
			return res;
		}

		static void deallocate(void* p, size_t)  {
			free(p);
		}

		static void* reallocate(void*p , size_t n)  {
			void* res = realloc(p, n);
			if (0 == res) res == oom_realloc(p, n);
			return res;
		}

		static void (*set_malloc_handler(void(*f)()))()  {   //返回的是一个函数指针，参数也是函数指针
			void (*old)() = __malloc_alloc_oom_handler;
			__malloc_alloc_oom_handler = f;
			return old;
		}

		static void free_all();
	};

	typedef __alloc_bigsize malloc_alloc;

	enum {__ALIGN = 8};
	enum {__MAXBYTES = 128};
	enum {__NFREELISTS = (__MAXBYTES / __ALIGN)};
	

	class Alloc 
	{
	
	private:
		union obj  {
			union obj* next;
			char client[1];
		};

		static obj* free_list[__NFREELISTS];
	private:
		static char* start_free;
		static char* end_free;
		static size_t heap_size;

	private:
		static size_t Round_Up(size_t bytes)  {
			return ((bytes + __ALIGN - 1) & ~(__ALIGN - 1));
		} 

		static size_t Freelist_Index(size_t bytes)  {
			return ((bytes + __ALIGN - 1) / __ALIGN - 1);
		}

		static void* refill(size_t n);
		static void* chunk_alloc(size_t size, int& nobjs);

	public:
		static void* allocate(size_t bytes);
		static void deallocate(void* ptr, size_t bytes);
		static void* reallocate(void* ptr, size_t old_sz, size_t new_sz);
	};

	template<typename T, typename TAlloc>
	class SimpleAlloc
	{
	public:
		static T* allocate(size_t n)  {
			return 0 == n ? 0 : static_cast<T*>(TAlloc::allocate(n * sizeof(T)));
		}

		static T* allocate()  {
			return static_cast<T*>(TAlloc::allocate(sizeof(T)));
		}

		static void deallocate(T* p, size_t n)  {
			if (0 != n)  {
				TAlloc::deallocate(p, sizeof(T) * n);
			}
		}

		static void deallocate(T* p)  {
			TAlloc::deallocate(p, sizeof(T));
		}
	};

}