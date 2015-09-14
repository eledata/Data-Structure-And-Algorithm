#ifndef _CPPCDS_NUMERIC_H_
#define _CPPCDS_NUMERIC_H_

// numeric就是数值类的一些运算函数，例如累加，内积等
namespace cppcds
{
	// 累加
	template <class InputIterator, class T>
	T cppcds_accumulate(InputIterator first, InputIterator last, T initvalue)
	{
		for (; first != last; ++first)
		{
			initvalue = initvalue + *(first);
		}

		return initvalue;
	}

	template <class InputIterator, class T, class BinaryOperation>
	T cppcds_accumulate(InputIterator first, InputIterator last, T initvaluem, BinaryOperation oper)
	{
		for (; first != last; ++first)
		{
			initvalue = oper(initvalue, *(first));
		}

		return initvalue;
	}

	// 内积
	template <class InputIterator1, class InputIterator2, class T>
	T cppcds_inner_product(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, T initvalue)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			initvalue = initvalue + (*(first1)*(*first2));
		}

		return initvalue;
	}

	template <class InputIterator1, class InputIterator2, class T, class BinaryOperation1, class BinaryOperation2>
	T cppcds_inner_product(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, T initvalue, BinaryOperation1 oper1, BinaryOperation2 oper2)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			initvalue = oper1(initvalue, oper2(*(first1, *(first2))));
		}

		return initvalue;
	}

	// 局部求和
	template <class InputIterator, class OutputIterator, class T>
	OutputIterator _cppcds_partial_sum(InputIterator first, InputIterator last, OutputIterator result, T*)
	{
		T value = *first;

		while (first != last)
		{
			value = *(++first) + value;
			*(++result) = value;
		}

		return result;
	}

	template <class InputIterator, class OutputIterator>
	OutputIterator cppcds_partial_sum(InputIterator first, InputIterator last, OutputIterator result)
	{
		return _cppcds_partial_sum(first, last, result, cppcds_value_type(first));
	}

	template <class InputIterator, class OutputIterator, class T, class BinaryOperation>
	OutputIterator _cppcds_partial_sum(InputIterator first, InputIterator last, OutputIterator result, T*, BinaryOperation oper)
	{
		T value = *first;

		while (first != last)
		{
			value = oper(*(++first), value);
			*(++result) = value;
		}

		return result;
	}

	template <class InputIterator, class OutputIterator, class BinaryOperation>
	OutputIterator cppcds_partial_sum(InputIterator first, InputIterator last, OutputIterator result, BinaryOperation oper)
	{
		return _cppcds_partial_sum(first, last, result, cppcds_value_type(first), oper);
	}

	// 相邻元素的差额
	template <class InputIterator, class OutputIterator, class T>
	OutputIterator _cppcds_adjacent_difference(InputIterator first, InputIterator last, OutputIterator result, T*)
	{
		T value = *first;

		while (++first != last)
		{
			T temp = *first;
			*(++result) = temp - value;
			value = temp;
		}

		return result;
	}

	template <class InputIterator, class OutputIterator, class T>
	OutputIterator cppcds_adjacent_difference(InputIterator first, InputIterator last, OutputIterator result)
	{
		return _cppcds_adjacent_difference(first, last, result, cppcds_value_type(first));
	}

	template <class InputIterator, class OutputIterator, class T, class BinaryOperation>
	OutputIterator _cppcds_adjacent_difference(InputIterator first, InputIterator last, OutputIterator result, T*, BinaryOperation oper)
	{
		T value = *first;

		while (++first != last)
		{
			T temp = *first;
			*(++result) = oper(temp, value);
			value = temp;
		}

		return result;
	}

	template <class InputIterator, class OutputIterator, class T, class BinaryOperation>
	OutputIterator cppcds_adjacent_difference(InputIterator first, InputIterator last, OutputIterator result, BinaryOperation oper)
	{
		return _cppcds_adjacent_difference(first, last, result, cppcds_value_type(first), oper);
	}

	// 求幂函数
	template <class T, class Integer, class Operation>
	T _cppcds_power(T x, Integer n, Operation oper)
	{
		if (n == 0)
		{
			return cppcds_identity_element(oper);	// 会return 1；
		}
		else
		{
			// 1010： 10		x:2		n 0101:5 x：4
			while ((n & 1) == 0)		// 第一位为0，那么就为0
			{
				n >>= 1;				// 这里就会向右移移一位
				x = oper(x, x);
			}
		}

		T result = x;		// 4
		n >>= 1;			// 0010 : 2

		while (n != 0)
		{
			x = oper(x, x);		// X 16
			if ((x & 1) != 0)
			{
				result = oper(result, x);
				n >>= 1;
			}
			return result;
		}
	}

	template <class T, class Integer>
	T cppcds_power(T x, Integer n)
	{
		return _cppcds_power(x, n, cppcds_multiplies<T>);
	}

	template <class T, class Integer>
	T cppcds_my_power(T x, Integer n)
	{

	}

	// 在某区间内给予递增值
	template <class ForwardIterator, class T>
	void cppcds_iota(ForwardIterator first, ForwardIterator last, T value)
	{
		while (first != last)
		{
			*(first++) = value++;
		}
	}
}
#endif