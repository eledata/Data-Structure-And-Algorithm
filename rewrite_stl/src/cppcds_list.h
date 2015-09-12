#ifndef _CPPCDS_LIST_H_
#define _CPPCDS_LIST_H_

namespace cppcds
{
	// ֻ˵������ǰ�����Ľڵ�Ļ������ݽṹ
	struct _cppcds_list_node_base
	{
		struct _cppcds_list_node_base* next;
		struct _cppcds_list_node_base* prev;
	};

	// �ڵ����ݽṹ
	template<class T>
	struct _cppcds_list_node: public _cppcds_list_node_base
	{
		T data;
	};

	// list��iterator�����ⲿ��iterator����ȡlist�е����ݣ��Լ�����list�Ķ�ȡģʽ��
	struct _cppcds_list_iterator_base
	{
		typedef size_t		size_type;
		typedef ptrdiff_t	difference_type;
		typedef bidirectional_iterator_tag iterator_category;	// list��iterator������
		_cppcds_list_node_base* _b_node;

		_cppcds_list_iterator_base(_cppcds_list_node_base* x): _b_node(x){}
		_cppcds_list_iterator_base(){}

		// �ڵ���ǰ�ߣ����������
		void _b_incr(){_b_node = _b_node->next;}
		void _b_decr(){_b_node = _b_node->prev;}

		bool operator==(const _cppcds_list_iterator_base& x)
		{
			return _b_node == x._b_node;
		}

		bool operator!=(const _cppcds_list_iterator_base& x)
		{
			return _b_node != x._b_node;
		}
	};


	template<class T, class ref, class ptr>
	struct _cppcds_list_iterator: public _cppcds_list_iterator_base
	{
		// һ����iterator�����ͱ���
		typedef _cppcds_list_iterator<T, T&, T*>				iterator;
		typedef _cppcds_list_iterator<T, const T&, const T*>	const_iterator;
		typedef _cppcds_list_iterator<T, ref, ptr>				self;

		typedef T		value_type;
		typedef ref		reference;
		typedef ptr		pointer;

		typedef _cppcds_list_node<T> node;

		_cppcds_list_iterator(node* x):_cppcds_list_iterator_base(x){}
		_cppcds_list_iterator(){}
		_cppcds_list_iterator(const iterator& x):_cppcds_list_iterator_base(x._b_node){}

		// ���������ݶ�ȡ�ķ�ʽ
		reference operator*()const{return ((node*)_b_node)->data;}
		pointer operator->()const{return &(operator*());}

		// ++a
		self& operator++()
		{
			this->_b_incr();
			return *this;
		}

		// a++;
		self operator++(int)
		{
			self tmp = *this;
			this->_b_incr();
			return tmp;
		}

		self& operator--()
		{
			this->_b_decr();
			return *this;
		}

		self operator--(int)
		{
			self tmp = *this;
			this->_b_decr();
			return tmp;
		}
	};

	template<class T, class Alloc = alloc>
	class _cppcds_list
	{
	public:
		typedef T					value_type;
		typedef value_type*			pointer;
		typedef const value_type*	const_pointer;
		typedef value_type&			reference;
		typedef const value_type	const_reference;
		typedef size_t				size_type;
		typedef ptrdiff_t			difference_type;

		// ���ڿ���������list�ˣ���Ϊlist��һ���֡������iterator�Ĺ���ԭ��
		typedef _cppcds_list_iterator<T, T&, T*>				iterator;
		typedef _cppcds_list_iterator<T, const T&, const T*>	const_iterator;

	private:
		typedef _cppcds_list_node<T>				_cppcds_list_node;
		typedef _cppcds_list_node_base				_cppcds_list_base_node;
		typedef _cppcds_list_iterator_base			_cppcds_list_iterator_base;

		// �ڴ���䷽��
		typedef simple_alloc<_cppcds_list_node, Alloc> _cppcds_list_node_allocate;

	public:
		// ������Щ��������¶����ͷʹ�ã�
		typedef _cppcds_list_node* _cppcds_link_type;

		_cppcds_list()
		{
			empty_init();
		}

		~_cppcds_list()
		{
			clear();
		}

		iterator begin()
		{
			return iterator((_cppcds_list_node*)node->next);
		}

		iterator end()
		{
			return iterator(node);
		}

		void push_front(const T& x)
		{
			insert(begin(), x);
		}

		void push_back(const T& x)
		{
			insert(end(), x);
		}

		void pop_front()
		{
			erase(front());
		}

		void pop_back()
		{
			iterator tmp = end();
			erase(--tmp);
		}

		reference front()
		{
			return *begin();
		}

		reference back()
		{
			return *(--end());
		}

		size_type size()
		{
			size_t result = 0;
			result = distance(begin(), end());
			return result;
		}

		bool empty()
		{
			return node->next == node;
		}

		// �Ƴ���������position��ָ�Ľڵ㣬������һ���ڵ�
		iterator erase(iterator position)
		{
			_cppcds_link_type prev = _cppcds_link_type(position._b_node->prev);
			_cppcds_link_type next = _cppcds_link_type(position._b_node->next);

			prev->next = next;
			next->prev = prev;

			_cppcds_destorynode(_cppcds_link_type(position._b_node));

			return iterator(next);
		}

		// �����������
		void clear()
		{
			_cppcds_link_type start = (_cppcds_link_type)node->next;
			while (start != node)
			{
				_cppcds_link_type tmp = start;
				start = (_cppcds_link_type)start->next;
				_cppcds_destorynode(tmp);
			}

			start->next = start;
			start->prev = start;
		}

		// ����ֵΪvalue������Ԫ�����
		void remove(const T& value)
		{
			iterator first = begin();
			iterator last = end();

			while (first != last)
			{
				iterator tmp = first;
				tmp++;
				if (*first == value)
				{
					erase(first);
				}
				first = tmp;
			}
		}

		// �Ƴ���������ͬ��Ԫ��
		void unique()
		{
			iterator first = begin();
			iterator last = end();

			while (first != last)
			{
				iterator tmp = first;
				tmp++;
				if (*first == *(tmp))
				{
					erase(first);
				}
				first = tmp;
			}
		}

		// �������õ�Ԫ��
		void reverse()
		{
			iterator last = begin();

			if (node->next == node || node->next->next == node)
			{
				return;
			}

			++last;
			while (last != end())
			{
				iterator first = last;
				++last;
				transfer(begin(), first, last);
			}
		}

		// ��x�ϵ�Ԫ�طŵ�postion֮ǰ
		void splice(iterator position, _cppcds_list& x)
		{
			if (!x.empty())
			{
				transfer(position, x.begin(), x.end());
			}
		}

		// ��x�����ϵ�Ԫ�غϲ���this֮�ϡ�
		void merge(_cppcds_list& x)
		{
			iterator first1 = begin();
			iterator last1 = end();

			iterator first2 = x.begin();
			iterator last2 = x.end();

			// ����ǰ���С���������ѭ������first1Ϊ������������
			while(first1 != last1 && first2 != last2)
			{
				if (*first2 < *first1)
				{
					iterator next = first2;
					transfer(first1, first2, ++next);
					first2 = next;
				} 
				else
				{
					++first1;
				}
			}

			// ���뻹��ʣ��ģ���ôȫ�����롣
			if (first2 != last2)
			{
				transfer(last1, first2, last2);
			}
		}

		void sort()
		{

		}


	private:
		_cppcds_link_type node;

		// ����ڵ�ռ�
		_cppcds_link_type _cppcds_get_node()
		{
			return _cppcds_list_node_allocate::allocate();
		}

		// �ջؽڵ�ռ�
		void _cppcds_abandon_node(_cppcds_link_type p)
		{
			_cppcds_list_node_allocate::deallocate(p);
		}

		// ����һ���µĽڵ�
		_cppcds_link_type _cppcds_createnode(const T& x)
		{
			_cppcds_link_type newnode = _cppcds_get_node();
			cppcds_construct(&newnode->data, x);

			return newnode;
		}

		// ���ٽڵ�
		void _cppcds_destorynode(_cppcds_link_type p)
		{
			cppcds_destory(p);
			_cppcds_abandon_node(p);
		}

		//����һ��ͷ��㡣
		void empty_init()
		{
			node = _cppcds_get_node();
			node->next = node;
			node->prev = node;
		}

		// tmp <-> position
		iterator insert(iterator position, const T& x)
		{
			_cppcds_link_type tmp = _cppcds_createnode(x);

			tmp->next = position._b_node;
			tmp->prev = position._b_node->prev;

			(_cppcds_link_type(position._b_node->prev))->next = tmp;
			position._b_node->prev = tmp;

			return iterator(tmp);
		}

		// [first, last)�ڵ�Ԫ���ƶ���position֮ǰ
		void transfer(iterator position, iterator first, iterator last)
		{
			if (position != last)
			{
				// �Ƚ�[first, last)�������
				last._b_node->prev->next = position._b_node;
				first._b_node->prev->next = last._b_node;
				position._b_node->prev->next = first._b_node;

				// ��ʱ�Ĺ����Ͳ���Ĺ�����
				_cppcds_link_type tmpfirst_prev = (_cppcds_link_type)position._b_node->prev;
				position._b_node->prev =  last._b_node->prev;
				last._b_node->prev = first._b_node->prev;
				first._b_node->prev = tmpfirst_prev;
			}
		}
	};


}	// �����ռ��β

#endif
