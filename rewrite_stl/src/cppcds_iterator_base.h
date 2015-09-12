#ifndef _CPPCDS_ITERATORBASE_H_
#define _CPPCDS_ITERATORBASE_H_

///////////////////////////////////////////////////////////
//		 input_iterator_tag		output_iterator_tag
//					forward_iterator_tag
//				   bidirectional_iterator_tag
//				   random_access_iterator_tag
// 以上表示迭代器的从属关系！~！
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//	input_iterator_tag				此迭代器所指的对象(Read only)
//	output_iterator_tag				此迭代器所指的对象(Write only)
//	forward_iterator_tag			允许写入型的算法（只能单向移动）
//	bidirectional_iterator_tag		允许双向移动
//	random_access_iterator_tag		前面四种只提供++, --;但是这位
//	仁兄可以提供所有的指针算术能力,++ -- +n -n p1<p2 p1-p2 p[n]
//  以上表示迭代器的功能关系！~！
///////////////////////////////////////////////////////////


namespace cppcds
{
	// 以下这个几个是标记的tag！在判别用哪种算法的时候起了很大的作用
	struct input_iterator_tag{};
	struct output_iterator_tag{};
	struct forward_iterator_tag: public input_iterator_tag{};
	struct bidirectional_iterator_tag: public forward_iterator_tag{};
	struct random_access_iterator_tag: public bidirectional_iterator_tag{};

	template<class T, class Distance>
	struct input_iterator
	{
		typedef input_iterator_tag	iterator_category;
		typedef T					value_type;
		typedef Distance			difference_type;
		typedef T*					pointer;
		typedef T&					reference;
	};

	struct output_iterator
	{
		typedef output_iterator_tag	iterator_category;
		typedef void				value_type;
		typedef void				difference_type;
		typedef void				pointer;
		typedef void				reference;
	};

	template<class T, class Distance>
	struct forward_iterator
	{
		typedef forward_iterator_tag	iterator_category;
		typedef T						value_type;
		typedef Distance				difference_type;
		typedef T*						pointer;
		typedef T&						reference;
	};

	template<class T, class Distance>
	struct bidirectional_iterator
	{
		typedef bidirectional_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef Distance					difference_type;
		typedef T*							pointer;
		typedef T&							reference;
	};

	template<class T, class Distance>
	struct random_access_iterator
	{
		typedef random_access_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef Distance					difference_type;
		typedef T*							pointer;
		typedef T&							reference;
	};

	// iterator 始祖
	template<class Category,		// iterator类别 
	class T,						// 类型
	class Distance = ptrdiff_t,		// 距离,两个指针之间的差相对应的类型
	class Pointer = T*,				// 指针
	class Reference = T&>			// 引用
	struct iterator
	{
		typedef Category	iterator_category;
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
	};

	// 特性的萃取机，通过typename的巧妙应用，将各个iterator_category，value_type等给显示出来。
	template <class Iterator>
	struct iterator_traits {
		typedef typename Iterator::iterator_category iterator_category;
		typedef typename Iterator::value_type        value_type;
		typedef typename Iterator::difference_type   difference_type;
		typedef typename Iterator::pointer           pointer;
		typedef typename Iterator::reference         reference;
	};

	// 偏特化的过程
	// 指针的版本
	template <class T>
	struct iterator_traits<T*> {
		typedef random_access_iterator_tag	iterator_category;	// 指针是可以随机存取的
		typedef T							value_type;
		typedef ptrdiff_t                   difference_type;
		typedef T*							pointer;
		typedef T&							reference;
	};

	// const 指针的版本
	template <class T>
	struct iterator_traits<const T*> {
		typedef random_access_iterator_tag iterator_category;
		typedef T							value_type;
		typedef ptrdiff_t                   difference_type;
		typedef const T*					pointer;
		typedef const T&					reference;
	};

	// 获取迭代器类型的函数:iterator_category()
	template <class Iterator>
	inline 
	typename iterator_traits<Iterator>::iterator_category	// 返回iterator_category类型
	cppcds_iterator_category(const Iterator&)
	{
		typedef typename iterator_traits<Iterator>::iterator_category category;
		return category();	// 由于iterator_category是没有成员的结构体，有默认构造函数
	}

	// 获取指针间的距离的类型
	template <class Iterator>
	inline
	typename iterator_traits<Iterator>::difference_type*
	cppcds_distance_type(const Iterator&)
	{
		return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
	}

	// 获取值类型
	template <class Iterator>
	inline
	typename iterator_traits<Iterator>::value_type*
	cppcds_value_type(const Iterator&)
	{
		return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
	}

	// distance函数，萃取工作现在进入作战状态
	// 下面这个是InputIterator类型的迭代器
	template <class InputIterator>
	inline
	typename iterator_traits<InputIterator>::difference_type
	_distance(InputIterator first, InputIterator last, input_iterator_tag)	// 这里发生了神奇的事情了
	{
		typename iterator_traits<InputIterator>::difference_type dis = 0;

		// 这就一般读的循环方式
		while (first != last)
		{
			++dis;
			++first;
		}

		return dis;
	}

	// 下面这个是randomaccessiterator类型的迭代器
	template <class RandomaccessIterator>
	inline
	typename iterator_traits<RandomaccessIterator>::difference_type
	_distance(RandomaccessIterator first, RandomaccessIterator last, random_access_iterator_tag)	// 这里发生了神奇的事情了
	{
		return last - first;
	}

	// 真正的distance的函数来了
	template <class Iterator>
	inline
	typename iterator_traits<Iterator>::difference_type
	distance(Iterator first, Iterator last)	
	{
		return _distance(first, last, cppcds_iterator_category(first));
	}

	// advance函数，向前前进的函数
	template <class InputIterator, class Distance>
	inline
	void
	_advance(InputIterator& i, Distance n, input_iterator_tag)
	{
		while (n--)
		{
			++i;
		}
	}

	template <class BidirectionalIterator, class Distance>
	inline
	void
	_advance(BidirectionalIterator& i, Distance n, bidirectional_iterator_tag)
	{
		if (n >= 0)		// 由于双向运动的迭代器可向前动，也可向后动。所以n的值可大于0，可小于0。
		{
			while (n--)
			{
				++i;
			}
		} 
		else
		{
			while (n++)
			{
				--i;
			}
		}
	}

	template <class RandomaccessIterator, class Distance>
	inline void
	_advance(RandomaccessIterator& i, Distance n, random_access_iterator_tag)
	{
		i += n;
	}

	template <class Iterator, class Distance>
	inline
	void
	advance(Iterator& i, Distance n)
	{
		_advance(i, n, cppcds_iterator_category(i));
	}
	// 
}	// 命名空间结尾

#endif