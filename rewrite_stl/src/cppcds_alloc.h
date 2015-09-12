#ifndef _CPPCDS_ALLOC_H_
#define _CPPCDS_ALLOC_H_

#include "cppcds_config.h"

#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>

namespace cppcds
{
	template <int _inst>
	class _cppcds_malloc_alloc_template
	{
	private:
		static void* oom_malloc(size_t);		// out of memory:oom
		static void* oom_realloc(void*, size_t);

	public:
		static void* allocate(size_t n)
		{
			void* result = malloc(n);
			if (result == NULL)				// ����û�гɹ������
			{
				result = oom_malloc(n);
			}

			return result;
		}

		static void deallocate(void* p)
		{
			free(p);
		}

		static void* reallocate(void* p, size_t new_size)
		{
			void* result = realloc(p, new_size);		// ָ����=����������*��realloc��Ҫ�ı��ڴ��С��ָ�������µĴ�С����
			//�µĴ�Сһ��Ҫ����ԭ���Ĵ�С��Ȼ�Ļ��ᵼ�����ݶ�ʧ��
			if (result == NULL)
			{
				result = oom_realloc(p, new_size);
			}

			return result;
		}
	};

	template <int _inst>
	void*
	_cppcds_malloc_alloc_template<_inst>::oom_malloc(size_t n)
	{
		void* result;

		for(;;)
		{
			result = malloc(n);
			if (result)
			{
				return (result);
			}
			else
			{
				exit(0);
			}
		}
	}

	template <int _inst>
	void*
		_cppcds_malloc_alloc_template<_inst>::oom_realloc(void* p, size_t n)
	{
		void* result;

		for(;;)
		{
			result = realloc(p, n);
			if (result)
			{
				return (result);
			}
			else
			{
				exit(0);
			}
		}
	}

	typedef _cppcds_malloc_alloc_template<0> mallloc_alloc;

	// default alloc
	template <int inst>
	class _cppcds_default_alloc_template
	{
	private:
		enum{MEM_ALIGN = 8};	// С���������ϵ��߽�
		enum{MAX_SMALL_MEM_SIZE_MAX = 128};	// С������������
		enum{MEM_FREE_LIST_COUNT = MAX_SMALL_MEM_SIZE_MAX/MEM_ALIGN};	// free-list�ĸ���

		// ���ϳ�8�ı���
		static size_t _cppcds_round_up(size_t _bytes) 
		{ 
			return (((_bytes) + (size_t) MEM_ALIGN - 1) & ~((size_t) MEM_ALIGN - 1)); 
		}

		// ��������Ĵ�С������ʹ�õڼ��ţ� n��0��ʼ
		static  size_t _cppcds_freelist_index(size_t _bytes) 
		{
			return (((_bytes) + (size_t)MEM_ALIGN - 1)/(size_t)MEM_ALIGN - 1);
		}

		// freelist�Ĺ���
		union obj
		{
			union obj* free_list_link;
			char client_data[1];
		};

		static obj* volatile free_list[MEM_FREE_LIST_COUNT];

		static void* cppcds_refill(size_t n);

		static char* cppcds_chunk_alloc(size_t size, int& nobjs);

		static char* cppcds_start_freelist;
		static char* cppcds_end_freelist;
		static size_t cppcds_heap_size;

	public:

		static void* allocate(size_t n)
		{
			void* ret = 0;
			obj* volatile *my_freelist;
			obj* result;
			// n ���� 128��ʱ�򣬵��õ�һ����allocate
			if (n > (size_t)MAX_SMALL_MEM_SIZE_MAX)
			{
				ret = mallloc_alloc::allocate(n);
				return ret;
			} 

			my_freelist = free_list + _cppcds_freelist_index(n);
			result = *my_freelist;

			// ���û���ҵ����õ�freelist�� ׼���������freelist
			if (result == 0)
			{
				void* r = cppcds_refill(_cppcds_round_up(n));
				return (r);
			}
			*my_freelist = result->free_list_link;
			return (result);
		}

		static void deallocate(void* p, size_t n)
		{
			obj* q = (obj*)p;
			obj* volatile *my_free_list;

			if (n > (size_t)MAX_SMALL_MEM_SIZE_MAX)
			{
				mallloc_alloc::deallocate(p);
			} 
			else
			{
				//Ѱ�Ҷ�Ӧ��freelist
				my_free_list = free_list + _cppcds_freelist_index(n);
				//����freelist����������
				q->free_list_link = *my_free_list;
				*my_free_list = q;
			}
		}

		static void* reallocate(void* p, size_t oldsize, size_t newsize);
	};

	template<int inst>
	char* _cppcds_default_alloc_template<inst>::cppcds_start_freelist = 0;

	template<int inst>
	char* _cppcds_default_alloc_template<inst>::cppcds_end_freelist = 0;

	template<int inst>
	size_t _cppcds_default_alloc_template<inst>::cppcds_heap_size = 0;

	template<int inst>
	typename _cppcds_default_alloc_template<inst>::obj* volatile 
		_cppcds_default_alloc_template<inst>::free_list[MEM_FREE_LIST_COUNT] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,};

	template <int inst>
	void*
	_cppcds_default_alloc_template<inst>::cppcds_refill(size_t n)
	{
		int nobjs = 2;
		// ���ڴ����ȡ�ÿ��ڴ�
		char* chunk = cppcds_chunk_alloc(n, nobjs);

		obj* volatile *my_free_list;
		obj* result;
		obj* current_obj;
		obj* next_obj;
		int i;

		// ��ֻ����һ���ʱ�򣬾ͷ���������ߣ�free listû���µĽڵ�
		if (nobjs == 1)
		{
			return (chunk);
		}

		my_free_list = free_list + _cppcds_freelist_index(n);
		result = (obj*)chunk;

		*my_free_list = next_obj = (obj*)(chunk + n);

		for (i = 1; ; i++)
		{
			current_obj = next_obj;
			next_obj = (obj*)((char*)next_obj + n);

			if (nobjs - 1 == i)
			{
				current_obj->free_list_link = 0;
				break;
			} 
			else
			{
				current_obj->free_list_link = next_obj;
			}
		}

		return (result);
	}

	template <int inst>
	char* 
	_cppcds_default_alloc_template<inst>::cppcds_chunk_alloc(size_t size, int& nobjs)
	{
		char* result;
		size_t total_bytes = size * nobjs;
		size_t bytes_left = cppcds_end_freelist - cppcds_start_freelist;
		size_t bytes_to_get = 0;

		if (bytes_left >= total_bytes)
		{
			result = cppcds_start_freelist;
			cppcds_start_freelist += total_bytes;
			return (result);
		} 
		else if(bytes_left >= size)
		{
			nobjs = (int)(bytes_left/size);
			total_bytes = nobjs * size;
			result = cppcds_start_freelist;
			cppcds_start_freelist += total_bytes;
			return (result);
		}else{
			// ��һ��������ڴ�صĴ�С�������
			bytes_to_get = 2 * total_bytes;

			if (bytes_left > 0)
			{
				obj* volatile* my_free_list = free_list + _cppcds_freelist_index(bytes_left);

				((obj*)cppcds_start_freelist)->free_list_link = *my_free_list;

				*my_free_list = (obj*)cppcds_start_freelist;
			}

			// ���ڴ������עˮ�ˡ�
			cppcds_start_freelist = (char*)malloc(bytes_to_get);
			if (cppcds_start_freelist == 0)
			{
				int i;
				obj* volatile *my_free_list, *p;

				for (i = size; i <= MAX_SMALL_MEM_SIZE_MAX; i += MEM_ALIGN)
				{
					my_free_list = free_list + _cppcds_freelist_index(i);
					p = *my_free_list;

					if (p != 0)
					{
						*my_free_list = p->free_list_link;
						cppcds_start_freelist = (char*)p;
						cppcds_end_freelist = cppcds_start_freelist + i;
						return(cppcds_chunk_alloc(size, nobjs));
					}
				}

				cppcds_end_freelist = 0;
				cppcds_start_freelist = (char*)mallloc_alloc::allocate(bytes_to_get);
			}

			cppcds_heap_size += bytes_to_get;
			// �������ˣ�����3���bug�������������ط���cppcds_start_freelist = cppcds_start_freelist + bytes_to_get;
			cppcds_end_freelist = cppcds_start_freelist + bytes_to_get;
			return (cppcds_chunk_alloc(size, nobjs));
		}
	}
	//
	//template<int inst>
	//void* _cppcds_default_alloc_template<inst>::reallocate(void* p, size_t oldsize, size_t newsize)
	//{
	//	void* result;
	//	size_t copy_sz;
	//
	//	if (oldsize > (size_t)MAX_SMALL_MEM_SIZE_MAX &&
	//		newsize > (size_t)MAX_SMALL_MEM_SIZE_MAX
	//		)
	//	{
	//		return(reallocate(p, newsize));
	//	}
	//
	//	if (_cppcds_round_up(oldsize) == _cppcds_round_up(newsize))
	//	{
	//		return(p);
	//	}
	//
	//	result = allocate(newsize);
	//}


	typedef _cppcds_default_alloc_template<0> alloc;

	template<class Tp, class Alloc>
	class simple_alloc
	{
	public:
		static Tp* allocate(size_t n)
		{
			return n == 0 ? 0 : (Tp*)Alloc::allocate(n*sizeof(Tp));
		}

		static Tp* allocate(void)
		{

			return (Tp*)Alloc::allocate(sizeof(Tp));
		}

		static void deallocate(Tp* p, size_t n)
		{
			if(n != 0)
			{
				Alloc::deallocate(p, n*sizeof(Tp));
			}
		}

		static void deallocate(Tp* p)
		{
			Alloc::deallocate(p, sizeof(Tp));
		}
	};

}	// �����ռ��β

#endif
