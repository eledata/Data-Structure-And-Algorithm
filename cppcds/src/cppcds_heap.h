#ifndef _CPPCDS_HEAP_H_
#define _CPPCDS_HEAP_H_

// 个人觉得下面的实现比较的狗屎！——！实现的不好！但是要尊重原著。。。。
namespace cppcds
{
	// holeindex value之前的区间大小,比较迷惑的是，要将holeindex用成下标！ topindex 堆顶, value 新进入的值!
	template <class RandomAccessIterator, class Distance, class T>
	void
	_push_heap(RandomAccessIterator first, Distance holeindex, Distance topindex, T value)
	{
		Distance parent = (holeindex - 1)/2;	// 找出父节点
		cout << parent << holeindex << endl;
		while (holeindex > topindex && *(first + parent) < value)	// value之前的区间要进行调整，给value空出最好的位置
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
		// last - first - 1： vaule值之前的区间要进行调整
		_push_heap(first, Distance((last - first) - 1), Distance(0), T(*(last - 1)));
	}

	template <class RandomAccessIterator>
	inline void
	push_heap(RandomAccessIterator first, RandomAccessIterator last)
	{
		// 向这里解析了first的distance type 和 value type;
		_push_heap_aux(first, last, cppcds_distance_type(first), cppcds_value_type(first));
	}

	template <class RandomAccessIterator, class Distance, class T>
	void
	_adjust_heap(RandomAccessIterator first, Distance holeindex, Distance len, T value)
	{
		Distance topindex = holeindex;
		Distance secondchild = 2*holeindex + 2;

		// 下面这样的解法比较恶心，因为下标从0开始的缘故。
		while (secondchild < len)
		{
			// 找出子节点中，最大的那个元素
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

		// 以下的函数证明了，用last-first用于长度的原因，因为value是被排出在外的，所以此时要加回来。
		// cout << value << holeindex  << *(first + topindex)<< endl;
		_push_heap(first, holeindex, topindex, value);	// holeindex 子节点，topindex 头结点
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

	// 将堆顶元素移到堆尾，然后用pop_back()将元素扔出去
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
			return;		// 此时不具备建堆的条件，一个元素怎么建堆
		}

		Distance len = last - first;
		Distance parent = (len - 2)/2;
		while (1)
		{
			_adjust_heap(first, parent, len, T(*(first + parent)));
			if (parent == 0)
			{
				return;	// 说明此时已经调整到了堆顶了，此时要跳出一个无限循环
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

	// cmp的版本
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