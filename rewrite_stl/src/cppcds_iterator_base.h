#ifndef _CPPCDS_ITERATORBASE_H_
#define _CPPCDS_ITERATORBASE_H_

///////////////////////////////////////////////////////////
//		 input_iterator_tag		output_iterator_tag
//					forward_iterator_tag
//				   bidirectional_iterator_tag
//				   random_access_iterator_tag
// ���ϱ�ʾ�������Ĵ�����ϵ��~��
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//	input_iterator_tag				�˵�������ָ�Ķ���(Read only)
//	output_iterator_tag				�˵�������ָ�Ķ���(Write only)
//	forward_iterator_tag			����д���͵��㷨��ֻ�ܵ����ƶ���
//	bidirectional_iterator_tag		����˫���ƶ�
//	random_access_iterator_tag		ǰ������ֻ�ṩ++, --;������λ
//	���ֿ����ṩ���е�ָ����������,++ -- +n -n p1<p2 p1-p2 p[n]
//  ���ϱ�ʾ�������Ĺ��ܹ�ϵ��~��
///////////////////////////////////////////////////////////


namespace cppcds
{
	// ������������Ǳ�ǵ�tag�����б��������㷨��ʱ�����˺ܴ������
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

	// iterator ʼ��
	template<class Category,		// iterator��� 
	class T,						// ����
	class Distance = ptrdiff_t,		// ����,����ָ��֮��Ĳ����Ӧ������
	class Pointer = T*,				// ָ��
	class Reference = T&>			// ����
	struct iterator
	{
		typedef Category	iterator_category;
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
	};

	// ���Ե���ȡ����ͨ��typename������Ӧ�ã�������iterator_category��value_type�ȸ���ʾ������
	template <class Iterator>
	struct iterator_traits {
		typedef typename Iterator::iterator_category iterator_category;
		typedef typename Iterator::value_type        value_type;
		typedef typename Iterator::difference_type   difference_type;
		typedef typename Iterator::pointer           pointer;
		typedef typename Iterator::reference         reference;
	};

	// ƫ�ػ��Ĺ���
	// ָ��İ汾
	template <class T>
	struct iterator_traits<T*> {
		typedef random_access_iterator_tag	iterator_category;	// ָ���ǿ��������ȡ��
		typedef T							value_type;
		typedef ptrdiff_t                   difference_type;
		typedef T*							pointer;
		typedef T&							reference;
	};

	// const ָ��İ汾
	template <class T>
	struct iterator_traits<const T*> {
		typedef random_access_iterator_tag iterator_category;
		typedef T							value_type;
		typedef ptrdiff_t                   difference_type;
		typedef const T*					pointer;
		typedef const T&					reference;
	};

	// ��ȡ���������͵ĺ���:iterator_category()
	template <class Iterator>
	inline 
	typename iterator_traits<Iterator>::iterator_category	// ����iterator_category����
	cppcds_iterator_category(const Iterator&)
	{
		typedef typename iterator_traits<Iterator>::iterator_category category;
		return category();	// ����iterator_category��û�г�Ա�Ľṹ�壬��Ĭ�Ϲ��캯��
	}

	// ��ȡָ���ľ��������
	template <class Iterator>
	inline
	typename iterator_traits<Iterator>::difference_type*
	cppcds_distance_type(const Iterator&)
	{
		return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
	}

	// ��ȡֵ����
	template <class Iterator>
	inline
	typename iterator_traits<Iterator>::value_type*
	cppcds_value_type(const Iterator&)
	{
		return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
	}

	// distance��������ȡ�������ڽ�����ս״̬
	// ���������InputIterator���͵ĵ�����
	template <class InputIterator>
	inline
	typename iterator_traits<InputIterator>::difference_type
	_distance(InputIterator first, InputIterator last, input_iterator_tag)	// ���﷢���������������
	{
		typename iterator_traits<InputIterator>::difference_type dis = 0;

		// ���һ�����ѭ����ʽ
		while (first != last)
		{
			++dis;
			++first;
		}

		return dis;
	}

	// ���������randomaccessiterator���͵ĵ�����
	template <class RandomaccessIterator>
	inline
	typename iterator_traits<RandomaccessIterator>::difference_type
	_distance(RandomaccessIterator first, RandomaccessIterator last, random_access_iterator_tag)	// ���﷢���������������
	{
		return last - first;
	}

	// ������distance�ĺ�������
	template <class Iterator>
	inline
	typename iterator_traits<Iterator>::difference_type
	distance(Iterator first, Iterator last)	
	{
		return _distance(first, last, cppcds_iterator_category(first));
	}

	// advance��������ǰǰ���ĺ���
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
		if (n >= 0)		// ����˫���˶��ĵ���������ǰ����Ҳ����󶯡�����n��ֵ�ɴ���0����С��0��
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
}	// �����ռ��β

#endif