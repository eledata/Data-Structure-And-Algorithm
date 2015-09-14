#ifndef _CPPCDS_UNINITIALIZED_H_
#define _CPPCDS_UNINITIALIZED_H_

namespace cppcds
{
	// cppcds_uninitialized_copy
	template <class InputIterator, class ForwardIterator>
	inline 
	ForwardIterator
	_cppcds_uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, _cppcds_true_type)
	{
		return cppcds_copy(first, last, result);
	}

	template <class InputIterator, class ForwardIterator>
	inline 
	ForwardIterator
	_cppcds_uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, _cppcds_false_type)
	{
		ForwardIterator cur = result;
		for (; first != last; ++first, ++cur)
		{
			cppcds_construct(&*cur, *first);
		}
		return result;
	}

	template <class InputIterator, class ForwardIterator, class T>
	inline 
	ForwardIterator
	_cppcds_uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result, T*)
	{
		typedef typename _cppcds_type_trait<T>::is_POD_type is_POD;
		return _cppcds_uninitialized_copy_aux(first, last, result, is_POD());
	}

	template <class InputIterator, class ForwardIterator>
	inline 
	ForwardIterator
	cppcds_uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result)
	{
		return _cppcds_uninitialized_copy(first, last, result, cppcds_value_type(first));
	}

	// char特化的版本
	inline char* cppcds_uninitialized_copy(const char* first, const char* last, char* result)
	{
		memmove(result, first, last - first);
		return result + (last - first);
	}
	
	// wchar_t特化版本
	inline wchar_t* cppcds_uninitialized_copy(const wchar_t* first, const wchar_t* last, wchar_t* result)
	{
		memmove(result, first, (last - first)*sizeof(wchar_t));
		return result + (last - first);
	}

	// _cppcds_uninitialized_fill
	template <class ForwardIterator, class Size, class T>
	inline
	ForwardIterator
	_cppcds_uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T& value, _cppcds_true_type)
	{
		return cppcds_fill(first, last, value);
	}

	template <class ForwardIterator, class Size, class T>
	inline
	ForwardIterator
	_cppcds_uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T& value, _cppcds_false_type)
	{
		ForwardIterator cur = first;
		for (; cur != last; ++cur)
		{
			cppcds_construct(&*cur, value);
		}
	}

	template <class ForwardIterator, class Size, class T, class Tp>
	inline
	ForwardIterator
	_cppcds_uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& value, Tp*)
	{
		typedef typename _cppcds_type_trait<T>::is_POD_type is_POD;

		return _cppcds_uninitialized_fill_aux(first, last, value, is_POD());
	}

	template <class ForwardIterator, class Size, class T>
	inline
	ForwardIterator
	cppcds_uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& value)
	{
		return _cppcds_uninitialized_fill(first, last, value, cppcds_value_type(first));
	}

	// _cppcds_uninitialized_fill_n
	template <class ForwardIterator, class Size, class T>
	inline
	ForwardIterator
	_cppcds_uninitialized_fill_n_aux(ForwardIterator first, Size size, const T& value, _cppcds_true_type)
	{
		return cppcds_fill_n(first, size, value);
	}

	template <class ForwardIterator, class Size, class T>
	inline
	ForwardIterator
	_cppcds_uninitialized_fill_n_aux(ForwardIterator first, Size size, const T& value, _cppcds_false_type)
	{
		ForwardIterator cur = first;
		for (; size > 0; --size, ++cur)
		{
			cppcds_construct(&*cur, value);
		}
	}

	template <class ForwardIterator, class Size, class T, class Tp>
	inline
	ForwardIterator
	_cppcds_uninitialized_fill_n(ForwardIterator first, Size size, const T& value, Tp*)
	{
		typedef typename _cppcds_type_trait<T>::is_POD_type is_POD;

		return _cppcds_uninitialized_fill_n_aux(first, size, value, is_POD());
	}

	template <class ForwardIterator, class Size, class T>
	inline
	ForwardIterator
	cppcds_uninitialized_fill_n(ForwardIterator first, Size size, const T& value)
	{
		return _cppcds_uninitialized_fill_n(first, size, value, cppcds_value_type(first));
	}


}	// 命名空间结尾

#endif
