#ifndef _CPPCDS_ALGOBASE_H_
#define _CPPCDS_ALGOBASE_H_

namespace cppcds
{
	// swap函数，用于交换元素
	template <class ForwardIterator1, class ForwardIterator2, class T>
	inline void _cppcds_iter_swap(ForwardIterator1 a, ForwardIterator2 b, T*)	// T*萃取出类别
	{
		T temp = *a;
		*a = *b;
		*b = temp;
	}

	template <class ForwardIterator1, class ForwardIterator2>
	inline void cppcds_iter_swap(ForwardIterator1 a, ForwardIterator2 b)
	{
		_cppcds_iter_swap(a, b, value_type(a));
	}

	template <class T>
	inline void
	cppcds_swap(T& a, T& b)
	{
		T temp = a;
		a = b;
		b = temp;
	}

	// min， max 顾名思义，就是取最大和最小值的函数
	template <class T>
	inline T const
	cppcds_min(const T& a, const T& b)
	{
		return a > b ? b : a;
	}

	template <class T>
	inline T const
	cppcds_max(const T& a, const T& b)
	{
		return a > b ? a : b;
	}

	// copy 函数：将first， last上的元素复制到result上面
	template <class InputIterator, class OutputIterator, class Distance>
	inline OutputIterator
	_cppcds_copy(InputIterator first, InputIterator last, OutputIterator result, random_access_iterator_tag, Distance*)
	{
		for (Distance n = last - first; n > 0; --n)
		{
			*result = *first;
			++first;
			++result;
		}

		return result;
	}

	template <class InputIterator, class OutputIterator, class Distance>
	inline OutputIterator
	_cppcds_copy(InputIterator first, InputIterator last, OutputIterator result, input_iterator_tag, Distance*)
	{
		while (first != last)
		{
			*result = * first;
			++first;
			++result;
		}
		return result;
	}
	// _cppcds_copy 以上两个函数都是辅助函数。
	template <class InputIterator, class OutputIterator>
	inline OutputIterator
	cppcds_copy(InputIterator first, InputIterator last, OutputIterator result)
	{
		return _cppcds_copy(first, last, result, cppcds_iterator_category(first), cppcds_value_type(first));
	}

	// 对于内置数据类型的copy函数
	template <class T>
	inline T*
	cppcds_copy(const T* first, T* last, T* result)
	{
		memmove(result, first, sizeof(T)*(last - first));
		return (result + (last - first));
	}

	// backward函数
	template <class BidirectionalIterator1, class BidirectionalIterator2, class Distance>
	inline BidirectionalIterator2
	_cppcds_backward(BidirectionalIterator1 first,
					 BidirectionalIterator1 last,
					 BidirectionalIterator2 result,
					 bidirectional_iterator_tag,
					 Distance*
					)
	{
		while (first != last)
		{
			*--result = *last;	// 从后往前覆盖
		}
		return result;
	}

	template <class RandomaccessIterator, class BidirectionalIterator, class Distance>
	inline BidirectionalIterator
	_cppcds_backward(RandomaccessIterator first,
		RandomaccessIterator last,
		BidirectionalIterator result,
		random_access_iterator_tag,
		Distance*)
	{
		for (Distance n = last - first; n > 0; --n)
		{
			*--result = *--last;
		}
		return result;
	}

	template <class BidirectionalIterator1, class BidirectionalIterator2>
	inline BidirectionalIterator2
	cppcds_backward(BidirectionalIterator1 first,
		BidirectionalIterator1 last,
		BidirectionalIterator2 result)
	{
		return _cppcds_backward(first, last, result, cppcds_iterator_category(first), cppcds_distance_type(first));
	}

	// 对于内置的类型而言
	//template <class T>
	//inline T*
	//cppcds_backward(T *first,
	//	T *last,
	//	T *result)
	//{
	//	const ptrdiff_t dis = last - first;
	//	memmove(result - dis, first, sizeof(T)*dis);
	//	return (result - dis);
	//}

	// fill 和fill_n函数，在区间上填充value的值
	template <class ForwardIterator, class T>
	void cppcds_fill(ForwardIterator first, ForwardIterator last, const T& value)
	{
		while (first != last)
		{
			*first = value;
			++first;
		}
	}

	template <class OutputIterator, class T>
	OutputIterator cppcds_fill_n(OutputIterator first, size_t n, const T& value)
	{
		for (; n > 0; --n, ++first)
		{
			*first = value;
		}

		return first;
	}

	// 对于单字节的类型
	inline void cppcds_fill(unsigned char* first, unsigned char* last, const unsigned char& c)
	{
		unsigned char temp = c;
		memset(first, temp, last - first);
	}

	inline void cppcds_fill(signed char* first, signed char* last, const signed char& c)
	{
		signed char temp = c;
		memset(first, static_cast<unsigned char>(temp), last - first);
	}

	inline void cppcds_fill(char* first, char* last, const char& c)
	{
		char temp = c;
		memset(first, static_cast<unsigned char>(temp), last - first);
	}

	// equal 和mismatch函数，equal就是验证两个区间是否相等，mismatch找到第一个不相等的位置
	template <class InputIterator1, class InputIterator2>
	_cppcds_pair<InputIterator1, InputIterator2>
	cppcds_mismatch(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1 != last1 && *first1 == *first2)
		{
			++first1;
			++first2;
		}
		return _cppcds_pair<InputIterator1, InputIterator2>(first1, first2);
	}

	template <class InputIterator1, class InputIterator2, class Aux>
	_cppcds_pair<InputIterator1, InputIterator2>
	cppcds_mismatch(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1 != last1 && Aux(*first1 == *first2))
		{
			++first1;
			++first2;
		}
		return _cppcds_pair<InputIterator1, InputIterator2>(first1, first2);
	}

	template <class InputIterator1, class InputIterator2>
	bool
	cppcds_equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1 != last1 && *first1 == *first2)
		{
			++first1;
			++first2;
		}

		return first1 == last1 ? true : false;
	}
}	// 命名空间结尾
#endif