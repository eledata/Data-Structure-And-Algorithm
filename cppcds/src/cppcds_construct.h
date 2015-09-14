#ifndef _CPPCDS_CONSTRUCT_H_
#define _CPPCDS_CONSTRUCT_H_

#include "cppcds_type_trait.h"

#include <new>

namespace cppcds
{
	// 用placement new来在分配好的内存上构造对象，具体可以看看placement new的用法。
	template<class T1, class T2>
	inline void cppcds_construct(T1* p, const T2& value)
	{
		new ((void*)p) T1(value);
	}

	template<class T>
	inline void cppcds_construct(T* p)
	{
		new ((void*)p) T();
	}

	// 用placement new用自己动手销毁对象
	template<class T>
	inline void cppcds_destory(T* p)
	{
		p->~T();
	}

	template<class _cppcds_ForwardIterator>
	void
	_cppcds_destory_aux(_cppcds_ForwardIterator first, _cppcds_ForwardIterator last, _cppcds_false_type)
	{
		for(; first != last; first++)
		{
			cppcds_destory(&*first);
		}
	}

	template<class _cppcds_ForwardIterator>
	void
	_cppcds_destroy_aux(_cppcds_ForwardIterator first, _cppcds_ForwardIterator last, _cppcds_true_type)
	{

	}

	template<class _cppcds_ForwardIterator, class T>
	inline void
	_cppcds_destory(_cppcds_ForwardIterator first, _cppcds_ForwardIterator last, T*)
	{
		typedef typename _cppcds_type_trait<T>::has_trivial_destructor trivial_destructor;
		_cppcds_destory_aux(first, last, trivial_destructor());
	}

	inline void cppcds_destory(char*, char*) {}
	inline void cppcds_destory(int*, int*) {}
	inline void cppcds_destory(long*, long*) {}
	inline void cppcds_destory(float*, float*) {}
	inline void cppcds_destory(double*, double*) {}

	template <class _cppcds_ForwardIterator>
	void
	cppcds_destory(_cppcds_ForwardIterator first, _cppcds_ForwardIterator last)
	{
		_cppcds_destory(first, last, cppcds_value_type(first));
	}

}	// 命名空间结尾

#endif