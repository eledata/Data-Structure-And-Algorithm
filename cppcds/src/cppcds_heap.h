#ifndef _CPPCDS_HEAP_H_
#define _CPPCDS_HEAP_H_

// ���˾��������ʵ�ֱȽϵĹ�ʺ��������ʵ�ֵĲ��ã�����Ҫ����ԭ����������
namespace cppcds
{
	// holeindex value֮ǰ�������С,�Ƚ��Ի���ǣ�Ҫ��holeindex�ó��±꣡ topindex �Ѷ�, value �½����ֵ!
	template <class RandomAccessIterator, class Distance, class T>
	void
	_push_heap(RandomAccessIterator first, Distance holeindex, Distance topindex, T value)
	{
		Distance parent = (holeindex - 1)/2;	// �ҳ����ڵ�
		cout << parent << holeindex << endl;
		while (holeindex > topindex && *(first + parent) < value)	// value֮ǰ������Ҫ���е�������value�ճ���õ�λ��
		{
			*(first + holeindex) = *(first + parent);
			holeindex = parent;
			parent = (holeindex - 1)/2;
		}

		*(first + holeindex) = value;
	}

	template <class RandomAccessIterator, class Distance, class T>
	inline void
	_push_heap_aux(RandomAccessIterator first, RandomAccessIterator last, Distance*, T* )
	{
		// last - first - 1�� vauleֵ֮ǰ������Ҫ���е���
		_push_heap(first, Distance((last - first) - 1), Distance(0), T(*(last - 1)));
	}

	template <class RandomAccessIterator>
	inline void
	push_heap(RandomAccessIterator first, RandomAccessIterator last)
	{
		// �����������first��distance type �� value type;
		_push_heap_aux(first, last, cppcds_distance_type(first), cppcds_value_type(first));
	}

	template <class RandomAccessIterator, class Distance, class T>
	void
	_adjust_heap(RandomAccessIterator first, Distance holeindex, Distance len, T value)
	{
		Distance topindex = holeindex;
		Distance secondchild = 2*holeindex + 2;

		// ���������Ľⷨ�Ƚ϶��ģ���Ϊ�±��0��ʼ��Ե�ʡ�
		while (secondchild < len)
		{
			// �ҳ��ӽڵ��У������Ǹ�Ԫ��
			if (*(first + secondchild) < *(first + (secondchild - 1)))
			{
				secondchild--;
			}

			*(first + holeindex) = *(first + secondchild);
			holeindex = secondchild;
			secondchild = (secondchild + 1)*2;
		}

		if (secondchild == len)
		{
			*(first + holeindex) = *(first + (secondchild - 1));
			holeindex = secondchild - 1;
		}

		// ���µĺ���֤���ˣ���last-first���ڳ��ȵ�ԭ����Ϊvalue�Ǳ��ų�����ģ����Դ�ʱҪ�ӻ�����
		// cout << value << holeindex  << *(first + topindex)<< endl;
		_push_heap(first, holeindex, topindex, value);	// holeindex �ӽڵ㣬topindex ͷ���
	}

	template <class RandomAccessIterator, class Distance, class T>
	inline void
	_pop_heap(RandomAccessIterator first, RandomAccessIterator last, RandomAccessIterator result, T value, Distance*)
	{
		*result = *first;
		_adjust_heap(first, Distance(0), Distance(last - first), value);
	}

	template <class RandomAccessIterator, class T>
	inline void
	_pop_heap_aux(RandomAccessIterator first, RandomAccessIterator last, T* )
	{
		_pop_heap(first, last - 1, last - 1, T(*(last - 1)), cppcds_distance_type(first));
	}

	// ���Ѷ�Ԫ���Ƶ���β��Ȼ����pop_back()��Ԫ���ӳ�ȥ
	template <class RandomAccessIterator>
	inline void
	pop_heap(RandomAccessIterator first, RandomAccessIterator last)
	{
		_pop_heap_aux(first, last, cppcds_value_type(first));
	}

	template <class RandomAccessIterator, class T, class Distance >
	void
	_make_heap(RandomAccessIterator first, RandomAccessIterator last, T*, Distance*)
	{
		if (last - first < 2)
		{
			return;		// ��ʱ���߱����ѵ�������һ��Ԫ����ô����
		}

		Distance len = last - first;
		Distance parent = (len - 2)/2;
		while (1)
		{
			_adjust_heap(first, parent, len, T(*(first + parent)));
			if (parent == 0)
			{
				return;	// ˵����ʱ�Ѿ��������˶Ѷ��ˣ���ʱҪ����һ������ѭ��
			}
			parent--;
		}
	}

	template <class RandomAccessIterator>
	inline void
	make_heap(RandomAccessIterator first, RandomAccessIterator last)
	{
		_make_heap(first, last, cppcds_value_type(first), cppcds_distance_type(first));
	}

	// cmp�İ汾
	template <class RandomAccessIterator, class Distance, class T, class Compare>
	void
	_push_heap(RandomAccessIterator first, Distance holeindex, Distance topindex, T value, Compare cmp)
	{
		Distance parent = (holeindex - 1)/2;
		while (holeindex > topindex && cmp(*(first + parent), value))
		{
			*(first + holeindex) = *(first + parent);
			holeindex = parent;
			parent = (holeindex - 1)/2;
		}

		*(first + holeindex) = value;
	}

	template <class RandomAccessIterator, class Distance, class T, class Compare>
	inline void
	_push_heap_aux(RandomAccessIterator first, RandomAccessIterator last, Distance*, T*, Compare cmp)
	{
		_push_heap(first, Distance((last - first) - 1), Distance(0), T(*(last - 1)), Compare cmp);
	}

	template <class RandomAccessIterator, class Compare>
	inline void
	push_heap(RandomAccessIterator first, RandomAccessIterator last, Compare cmp)
	{
		_push_heap_aux(first, last, cppcds_distance_type(first), cppcds_value_type(first), cmp);
	}

	template <class RandomAccessIterator, class Distance, class T, class Compare>
	void
	_adjust_heap(RandomAccessIterator first, Distance holeindex, Distance len, T value, Compare cmp)
	{
		Distance topindex = holeindex;
		Distance secondchild = 2*holeindex + 2;

		while (secondchild < len)
		{
			if (cmp(*(first + secondchild), *(first + (secondchild - 1))))
			{
				secondchild--;
			}

			*(first + holeindex) = *(first + secondchild);
			holeindex = secondchild;
			secondchild = (secondchild + 1)*2;
		}

		if (secondchild == len)
		{
			*(first + holeindex) = *(first + (secondchild - 1));
			holeindex = secondchild - 1;
		}

		_push_heap(first, holeindex, topindex, value);
	}

	template <class RandomAccessIterator, class Distance, class T, class Compare>
	inline void
	_pop_heap(RandomAccessIterator first, RandomAccessIterator last, RandomAccessIterator result, T value, Distance*, Compare cmp)
	{
		*result = *first;
		_adjust_heap(first, Distance(0), Distance(last - first), value, cmp);
	}

	template <class RandomAccessIterator, class T, class Compare>
	inline void
	_pop_heap_aux(RandomAccessIterator first, RandomAccessIterator last, T*, Compare cmp)
	{
		_pop_heap(first, last - 1, last - 1, T(*(last - 1)), cppcds_distance_type(first), cmp);
	}

	template <class RandomAccessIterator, class Compare>
	inline void
	pop_heap(RandomAccessIterator first, RandomAccessIterator last, Compare cmp)
	{
		_pop_heap_aux(first, last, cppcds_value_type(first), cmp);
	}

	template <class RandomAccessIterator, class T, class Distance, class Compare>
	void
	_make_heap(RandomAccessIterator first, RandomAccessIterator last, T*, Distance*, Compare cmp)
	{
		if (last - first < 2)
		{
			return;		
		}

		Distance len = last - first;
		Distance parent = (len - 2)/2;
		while (1)
		{
			_adjust_heap(first, parent, len, T(*(first + parent)), cmp);
			if (parent == 0)
			{
				return;	
			}
			parent--;
		}
	}

	template <class RandomAccessIterator, class Compare>
	inline void
	make_heap(RandomAccessIterator first, RandomAccessIterator last)
	{
		_make_heap(first, last, cppcds_value_type(first), cppcds_distance_type(first), cmp);
	}
}

#endif