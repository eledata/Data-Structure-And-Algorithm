#ifndef _CPPCDS_ALGO_H_
#define _CPPCDS_ALGO_H_

namespace cppcds
{
	// cppcds_median函数,取中间数
	template <class T>
	inline const T& cppcds_median(const T& a, const T& b, const T& c)
	{
		if (a < b)
		{
			if (b < c)
			{
				return b;
			} 
			else if(a < c)
			{
				return c;
			}
			else
			{
				return a;
			}
		} 
		else if(a < c)
		{
			return a;
		}
		else if(b < c)
		{
			return c;
		}
		else
		{
			return b;
		}
	}

	template <class T, class Compare>
	inline const T& cppcds_median(const T& a, const T& b, const T& c, Compare cmp)
	{
		if (cmp(a, b))
		{
			if (cmp(b, c))
			{
				return b;
			} 
			else if(cmp(a, c))
			{
				return c;
			}
			else
			{
				return a;
			}
		} 
		else if(cmp(a, c))
		{
			return a;
		}
		else if(cmp(b, c))
		{
			return c;
		}
		else
		{
			return b;
		}
	}

	// for_each 对于区间上的所有元素应用某一函数
	template <class InputIterator, class Function>
	Function cppcds_for_each(InputIterator first, InputIterator last, Function func)
	{
		for (; first != last; ++first)
		{
			func(*first);
		}
		return func;
	}

	// find 和find_if 函数，区间上找元素
	template <class InputIterator, class T>
	inline InputIterator
	_cppcds_find(InputIterator first, InputIterator last, const T& vaule, input_iterator_tag)
	{
		while (first != last)
		{
			if (*first == value)
			{
				return first;
			}
			++first;
		}
	}

	template <class InputIterator, class T>
	inline InputIterator
	cppcds_find(InputIterator first, InputIterator last, const T& value)
	{
		return _cppcds_find(first, last, value, cppcds_iterator_category(first));
	}

	template <class InputIterator, class T, class Operation>
	inline InputIterator
	_cppcds_find_if(InputIterator first, InputIterator last, Operation oper, input_iterator_tag)
	{
		while (first != last)
		{
			if (oper(*first))
			{
				return first;
			}
			++first;
		}
	}

	template <class InputIterator, class T, class Operation>
	inline InputIterator
	cppcds_find_if(InputIterator first, InputIterator last, Operation oper)
	{
		return _cppcds_find_if(first, last, oper, cppcds_iterator_category(first));
	}

	// adjacent_find.寻找两个连续相等的元素
	template <class ForwardIterator>
	ForwardIterator cppcds_adjacent_find(ForwardIterator first, ForwardIterator last)
	{
		if (first == last)
		{
			return first;
		}

		ForwardIterator next = first;
		while (++next != last)
		{
			if (*(first) == *(next))
			{
				return first;
			}
			first = next;
		}
		return last;
	}

	template <class ForwardIterator, class BinaryOperation>
	ForwardIterator cppcds_adjacent_find(ForwardIterator first, ForwardIterator last, BinaryOperation boper)
	{
		if (first == last)
		{
			return first;
		}

		ForwardIterator next = first;
		while (++next != last)
		{
			if (boper(*first, next))
			{
				return first;
			}
			first = next;
		}
		return last;
	}

	// count 和 count_if函数：这个版本呢，是用n返回value在区间中的个数

	template <class InputIterator, class T, class Size>
	void count(InputIterator first, InputIterator last, const T& value, Size& size)
	{
		while (first != last)
		{
			if (*first == value)
			{
				++size;
			}
			++first;
		}
	}

	template <class InputIterator, class Size, class Opearation>
	void count_if(InputIterator first, InputIterator last, Size& size, Opearation oper)
	{
		while (first != last)
		{
			if (oper(*first))
			{
				++size;
			}
			++first;
		}
	}

	// search,寻找在子区间第一次出现的位置
	template <class ForwardIterator1, class ForwardIterator2>
	ForwardIterator1 cppcds_search(ForwardIterator1 first1, ForwardIterator1 last1,
							ForwardIterator2 first2, ForwardIterator2 last2)
	{
		 // 测试是否为空区间
		if (first1 == last1 || first2 == last2)
		{
			return first1;
		}

		// 子区间有一个元素的情况
		ForwardIterator2 temp = first2;
		++temp;
		if (temp == last2)
		{
			return cppcds_find(first1, last1, *first2);
		}

		ForwardIterator2 fi1, fi2;
		fi1 = first2;
		++fi1;

		ForwardIterator1 current;
		current = first1;

		while (first1 != last1)
		{
			first1 = cppcds_find(first1, last1, *first2);
			if (first1 == last1)	// 说明说查找的区间只有一个元素
			{
				return last1;
			}

			// 将下一个元素弄进来。
			fi2 = fi1;
			current = first1;

			// current就是最后一个元素，那么就没得玩了。
			if (++current == last1)
			{
				return last1;
			}

			// current fi2的比较
			while (*current == *fi2)
			{
				if (++fi2 == last2)	 // fi2是最后一个元素，那么first1是find返回的位置，此时就是要找的区间的位置
				{
					return first1;
				}

				// current是最后一个元素，那么就是返回last
				if (++current == last1)
				{
					return last1;
				}
			}
			++first1;
		}
		return first1;
	}

	// 还没整好！
	//template <class ForwardIterator1, class ForwardIterator2, BinaryOperation opea>
	//ForwardIterator1 search(ForwardIterator1 first1, ForwardIterator1 last1,
	//	ForwardIterator2 first2, ForwardIterator2 last2)
	//{
	//	// 测试是否为空区间
	//	if (first1 == last1 || first2 == last2)
	//	{
	//		return first1;
	//	}

	//	// 子区间有一个元素的情况
	//	ForwardIterator2 temp = first2;
	//	++temp;
	//	if (temp == last2)
	//	{
	//		while (first1 != last1 && !opea(*first1, *first2))
	//		{
	//			++first1;
	//		}
	//		return first1;
	//	}

	//	ForwardIterator2 fi1, fi2;
	//	fi1 = first2;
	//	++fi1;

	//	ForwardIterator1 current;
	//	current = first1;

	//	while (first1 != last1)
	//	{
	//		while (first1 != last1 && !opea(*first1, *first2))
	//		{
	//			++first1;
	//		}

	//		if (first1 == last1)	// 说明说查找的区间只有一个元素
	//		{
	//			return last1;
	//		}

	//		// 将下一个元素弄进来。
	//		fi2 = fi1;
	//		current = first1;

	//		// current就是最后一个元素，那么就没得玩了。
	//		if (++current == last1)
	//		{
	//			return last1;
	//		}

	//		// current fi2的比较
	//		while (*current == *fi2)
	//		{
	//			if (++fi2 == last2)	 // fi2是最后一个元素，那么first1是find返回的位置，此时就是要找的区间的位置
	//			{
	//				return first1;
	//			}

	//			// current是最后一个元素，那么就是返回last
	//			if (++current == last1)
	//			{
	//				return last1;
	//			}
	//		}
	//		++first1;
	//	}
	//	return first1;
	//}
	//template <class ForwardIterator1, class Count, class T>
	//ForwardIterator1 cppcds_search_n(ForwardIterator1 first1, ForwardIterator1 last1,
	//	Count count, const T& value)
	//{
	//	if (const <= 0)
	//	{
	//		return first1;
	//	}
	//	else
	//	{
	//		first1 = cppcds_find(first1, last1, value);
	//		while (first1 != last1)
	//		{
	//			Count temp = count - 1;		// 由于找到value的第一个位置

	//		}
	//	}
	//}

	// 指定区间的交换
	template <class ForwardIterator1, class ForwardIterator2>
	ForwardIterator2 cppcds_swap_ranges(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2)
	{
		while (first1 != last1)
		{
			cppcds_iter_swap(first1, first2);
			++first1;
			++first2;
		}

		return first2;
	}

	// 以两个序列为基础，交互作用产生第三个序列
	template <class ForwardIterator1, class ForwardIterator2, class OutputIterator, class BinaryOperation>
	OutputIterator cppcds_transform(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, OutputIterator result, BinaryOperation boper)
	{
		while (first1 != last1)
		{
			*result = boper(*first1, *first2);
			++first1;
			++first2;
			++result;
		}

		return result;
	}

	template <class ForwardIterator1, class OutputIterator, class Operation>
	OutputIterator cppcds_transform(ForwardIterator1 first1, ForwardIterator1 last1, OutputIterator result, Operation boper)
	{
		while (first1 != last1)
		{
			*result = oper(*first1);
			++first1;
			++result;
		}

		return result;
	}

	// 将区间内符合条件的元素替换成新的元素
	template <class ForwardIterator, class T>
	ForwardIterator cppcds_replace(ForwardIterator first, ForwardIterator last, const T& old_value, const T& new_value)
	{
		while (first != last)
		{
			if (*first == old_value)
			{
				*first = new_value;
			}
			++first;
		}

		return first;
	}

	// 有条件的替换
	template <class ForwardIterator, class T, class Operation>
	ForwardIterator cppcds_replace_if(ForwardIterator first, ForwardIterator last, const T& new_value, Operation oper)
	{
		while (first != last)
		{
			if (oper(*first))
			{
				*first = new_value;
			}
			++first;
		}

		return first;
	}

	// 复制整个区间，将某类元素替换成新值。
	template <class ForwardIterator, class OutputIterator, class T>
	ForwardIterator cppcds_replace_copy(ForwardIterator first, ForwardIterator last, OutputIterator result, const T& old_value, const T& new_value)
	{
		while (first != last)
		{
			// *result = *first == old_value ? new_value : *first;	这样的实现的方式也是不错的。
			if (*first == old_value)
			{
				*result = new_value;
				continue;
			}

			*result = *first;
		}

		return result;
	}

	template <class ForwardIterator, class OutputIterator, class T, class Operation>
	ForwardIterator cppcds_replace_copy_if(ForwardIterator first, ForwardIterator last, OutputIterator result, const T& old_value, const T& new_value, Operation oper)
	{
		while (first != last)
		{
			if (oper(*first, old_value))
			{
				*result = new_value;
				continue;
			}

			*result = *first;
		}

		return result;
	}

	// 以某项操作的结果替换每一个元素
	template <class ForwardIterator, class Generator>
	void cppcds_generate(ForwardIterator first, ForwardIterator last, Generator gen)
	{
		while (first != last)
		{
			*first = gen();
			++first;
		}
	}

	// 以某项操作的结果替换n个元素
	template <class OutputIterator, class T, class Generator>
	OutputIterator cppcds_generate_n(OutputIterator first, T n, Generator gen)
	{
		for (; n > 0; --n, ++first)
		{
			*first = gen();
		}

		return first;
	}

	// 将不等于某特定值的元素全部复制到它处
	template <class InputIterator, class OutputIterator, class T>
	OutputIterator cppcds_remove_copy(InputIterator first, InputIterator last, OutputIterator result, const T& value)
	{
		while (first != last)
		{
			if (!(*first, value))
			{
				*result = *first;
				++first;
				++result;
				continue;
			}

			++first;
		}

		return result;
	}

	// 将不满足某准则的元素全部复制到别处
	template <class InputIterator, class OutputIterator, class T, class Operation>
	OutputIterator cppcds_remove_copy_if(InputIterator first, InputIterator last, OutputIterator result, const T& value, Operation oper)
	{
		while (first != last)
		{
			if (!oper(*first, value))
			{
				*result = *first;
				++first;
				++result;
				continue;
			}

			++first;
		}

		return result;
	}

	// 将等于某特定值的元素全部移除
	template <class ForwardIterator, class T>
	ForwardIterator cppcds_remove(ForwardIterator first, ForwardIterator last, const T& value)
	{
		first = cppcds_find(first, last, value);
		ForwardIterator temp = first;

		return first == last ? first : cppcds_remove_copy(++temp, last, first, value);
	}

	template <class ForwardIterator, class T, class Operatrion>
	ForwardIterator cppcds_remove_if(ForwardIterator first, ForwardIterator last, Operatrion oper)
	{
		first = cppcds_find_if(first, last, oper);
		ForwardIterator temp = first;

		return first == last ? first : cppcds_remove_copy_if(++temp, last, first, oper);
	}

	// 移除毗邻的重复元素
	template <class InputIterator, class OutputIterator, class T>
	OutputIterator _cppcds_unique(InputIterator first, InputIterator last, OutputIterator result, T*)
	{
		T value = *first;
		*result = value;

		while (++first != last)
		{
			if (!(value == *first))
			{
				value = *first;
				*++result = value;
			}
		}

		return ++result;
	}

	template <class InputIterator, class OutputIterator>
	OutputIterator _cppcds_unique(InputIterator first, InputIterator last, OutputIterator result, output_iterator_tag)
	{
		return _cppcds_unique(first, last, result, cppcds_value_type(first));
	}

	template <class InputIterator, class ForwardIterator>
	OutputIterator _cppcds_unique(InputIterator first, InputIterator last, ForwardIterator result, forward_iterator_tag)
	{
		*result = *first;

		while (++first != last)
		{
			if (!(result == *first))
			{
				*++result = *first;
			}
		}

		return ++result;
	}

	template <class InputIterator, class OutputIterator>
	OutputIterator cppcds_unique(InputIterator first, InputIterator last, OutputIterator result)
	{
		if (first == last)
		{
			return first;
		}
		return _cppcds_unique(first, last, result, cppcds_iterator_category(first));
	}

	template <class InputIterator, class OutputIterator, class T, class BinaryOperatrion>
	OutputIterator _cppcds_unique(InputIterator first, InputIterator last, OutputIterator result, T*, BinaryOperatrion boper)
	{
		T value = *first;
		*result = value;

		while (++first != last)
		{
			if (!boper(value, *first))
			{
				value = *first;
				*++result = value;
			}
		}

		return ++result;
	}

	template <class InputIterator, class OutputIterator, class BinaryOperatrion>
	OutputIterator _cppcds_unique(InputIterator first, InputIterator last, OutputIterator result, output_iterator_tag, BinaryOperatrion boper)
	{
		return _cppcds_unique(first, last, result, cppcds_value_type(first), boper);
	}

	template <class InputIterator, class ForwardIterator, class BinaryOperatrion>
	OutputIterator _cppcds_unique(InputIterator first, InputIterator last, ForwardIterator result, forward_iterator_tag, BinaryOperatrion boper)
	{
		*result = *first;

		while (++first != last)
		{
			if (!boper(result, *first))
			{
				*++result = *first;
			}
		}

		return ++result;
	}

	template <class InputIterator, class OutputIterator>
	OutputIterator cppcds_unique(InputIterator first, InputIterator last, OutputIterator result, BinaryOperatrion boper)
	{
		if (first == last)
		{
			return first;
		}
		return _cppcds_unique(first, last, result, cppcds_iterator_category(first), boper);
	}

	// 将元素逆转
	














































}	// 命名空间结尾
#endif