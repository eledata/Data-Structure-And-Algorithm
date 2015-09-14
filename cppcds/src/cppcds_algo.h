#ifndef _CPPCDS_ALGO_H_
#define _CPPCDS_ALGO_H_

namespace cppcds
{
	// cppcds_median����,ȡ�м���
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

	// for_each ���������ϵ�����Ԫ��Ӧ��ĳһ����
	template <class InputIterator, class Function>
	Function cppcds_for_each(InputIterator first, InputIterator last, Function func)
	{
		for (; first != last; ++first)
		{
			func(*first);
		}
		return func;
	}

	// find ��find_if ��������������Ԫ��
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

	// adjacent_find.Ѱ������������ȵ�Ԫ��
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

	// count �� count_if����������汾�أ�����n����value�������еĸ���

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

	// search,Ѱ�����������һ�γ��ֵ�λ��
	template <class ForwardIterator1, class ForwardIterator2>
	ForwardIterator1 cppcds_search(ForwardIterator1 first1, ForwardIterator1 last1,
							ForwardIterator2 first2, ForwardIterator2 last2)
	{
		 // �����Ƿ�Ϊ������
		if (first1 == last1 || first2 == last2)
		{
			return first1;
		}

		// ��������һ��Ԫ�ص����
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
			if (first1 == last1)	// ˵��˵���ҵ�����ֻ��һ��Ԫ��
			{
				return last1;
			}

			// ����һ��Ԫ��Ū������
			fi2 = fi1;
			current = first1;

			// current�������һ��Ԫ�أ���ô��û�����ˡ�
			if (++current == last1)
			{
				return last1;
			}

			// current fi2�ıȽ�
			while (*current == *fi2)
			{
				if (++fi2 == last2)	 // fi2�����һ��Ԫ�أ���ôfirst1��find���ص�λ�ã���ʱ����Ҫ�ҵ������λ��
				{
					return first1;
				}

				// current�����һ��Ԫ�أ���ô���Ƿ���last
				if (++current == last1)
				{
					return last1;
				}
			}
			++first1;
		}
		return first1;
	}

	// ��û���ã�
	//template <class ForwardIterator1, class ForwardIterator2, BinaryOperation opea>
	//ForwardIterator1 search(ForwardIterator1 first1, ForwardIterator1 last1,
	//	ForwardIterator2 first2, ForwardIterator2 last2)
	//{
	//	// �����Ƿ�Ϊ������
	//	if (first1 == last1 || first2 == last2)
	//	{
	//		return first1;
	//	}

	//	// ��������һ��Ԫ�ص����
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

	//		if (first1 == last1)	// ˵��˵���ҵ�����ֻ��һ��Ԫ��
	//		{
	//			return last1;
	//		}

	//		// ����һ��Ԫ��Ū������
	//		fi2 = fi1;
	//		current = first1;

	//		// current�������һ��Ԫ�أ���ô��û�����ˡ�
	//		if (++current == last1)
	//		{
	//			return last1;
	//		}

	//		// current fi2�ıȽ�
	//		while (*current == *fi2)
	//		{
	//			if (++fi2 == last2)	 // fi2�����һ��Ԫ�أ���ôfirst1��find���ص�λ�ã���ʱ����Ҫ�ҵ������λ��
	//			{
	//				return first1;
	//			}

	//			// current�����һ��Ԫ�أ���ô���Ƿ���last
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
	//			Count temp = count - 1;		// �����ҵ�value�ĵ�һ��λ��

	//		}
	//	}
	//}

	// ָ������Ľ���
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

	// ����������Ϊ�������������ò�������������
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

	// �������ڷ���������Ԫ���滻���µ�Ԫ��
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

	// ���������滻
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

	// �����������䣬��ĳ��Ԫ���滻����ֵ��
	template <class ForwardIterator, class OutputIterator, class T>
	ForwardIterator cppcds_replace_copy(ForwardIterator first, ForwardIterator last, OutputIterator result, const T& old_value, const T& new_value)
	{
		while (first != last)
		{
			// *result = *first == old_value ? new_value : *first;	������ʵ�ֵķ�ʽҲ�ǲ���ġ�
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

	// ��ĳ������Ľ���滻ÿһ��Ԫ��
	template <class ForwardIterator, class Generator>
	void cppcds_generate(ForwardIterator first, ForwardIterator last, Generator gen)
	{
		while (first != last)
		{
			*first = gen();
			++first;
		}
	}

	// ��ĳ������Ľ���滻n��Ԫ��
	template <class OutputIterator, class T, class Generator>
	OutputIterator cppcds_generate_n(OutputIterator first, T n, Generator gen)
	{
		for (; n > 0; --n, ++first)
		{
			*first = gen();
		}

		return first;
	}

	// ��������ĳ�ض�ֵ��Ԫ��ȫ�����Ƶ�����
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

	// ��������ĳ׼���Ԫ��ȫ�����Ƶ���
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

	// ������ĳ�ض�ֵ��Ԫ��ȫ���Ƴ�
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

	// �Ƴ����ڵ��ظ�Ԫ��
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

	// ��Ԫ����ת
	














































}	// �����ռ��β
#endif