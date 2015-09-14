#ifndef _CPPCDS_SLIST_H_
#define _CPPCDS_SLIST_H_

#include "cppcds_config.h"

namespace cppcds
{
	struct _cppcds_slist_node_base
	{
		_cppcds_slist_node_base* next;
	};

	// 将节点编织起来，形成一条链子。穿成链子的是这个家伙：_cppcds_slist_node_base
	inline _cppcds_slist_node_base*
		_cppcds_make_link(_cppcds_slist_node_base* prev_node,
		_cppcds_slist_node_base* new_node)
	{
		new_node->next = prev_node->next;
		prev_node->next = new_node;
		return new_node;
	}

	inline _cppcds_slist_node_base*
		_cppcds_previous(_cppcds_slist_node_base* head,
		const _cppcds_slist_node_base* node)
	{
		while (head && head->next != node)
		{
			head = head->next;
		}

		return head;
	}

	inline const _cppcds_slist_node_base*
		_cppcds_previous(const _cppcds_slist_node_base* head,
		const _cppcds_slist_node_base* node)
	{
		while (head && head->next != node)
		{
			head = head->next;
		}

		return head;
	}

	// 将(before_first,before_last]放到pos之后!~_~!
	inline void _cppcds_splice_after(_cppcds_slist_node_base* pos,
		_cppcds_slist_node_base* before_first,
		_cppcds_slist_node_base* before_last)
	{
		if (pos != before_first && pos != before_last)
		{
			_cppcds_slist_node_base* first = before_first->next;
			_cppcds_slist_node_base* after = pos->next;

			before_first->next = before_last->next;
			pos->next = first;
			before_last->next = after;
		}
	}

	// 单链表的反转
	inline _cppcds_slist_node_base* _cppcds_slist_reverse(_cppcds_slist_node_base* node)
	{
		_cppcds_slist_node_base* result = node;
		node = node->next;
		result->next = NULL;

		while (node)
		{
			_cppcds_slist_node_base* temp = node->next;
			node->next = result;
			result = node;
			node = temp;
		}

		return result;
	}

	// 单链表的长度
	size_t _cppcds_slist_size(_cppcds_slist_node_base* node)
	{
		size_t result = 0;
		for (; node != NULL; node = node->next)
		{
			++result;
		}
		return result;
	}

	// slist的节点，继承了_cppcds_slist_node_base，本身带有data
	template<class T>
	struct _cppcds_slist_node: public _cppcds_slist_node_base
	{
		T data;
	};

	// 迭代器
	struct _cppcds_slist_iterator_base
	{
		typedef size_t					size_type;
		typedef ptrdiff_t				difference_type;
		typedef forward_iterator_tag	iterator_tag;

		_cppcds_slist_node_base* _b_node;

		_cppcds_slist_iterator_base(_cppcds_slist_node_base* x):_b_node(x){}

		void _b_incr(){_b_node = _b_node->next;}

		bool operator==(const _cppcds_slist_iterator_base& x)const
		{
			return _b_node == x._b_node;
		}

		bool operator!=(const _cppcds_slist_iterator_base& x)const
		{
			return _b_node != x._b_node;
		}
	};

	template<class T, class ref, class ptr>
	struct _cppcds_slist_iterator: public _cppcds_slist_iterator_base
	{
		typedef _cppcds_slist_iterator<T, T&, T*>				iterator;
		typedef _cppcds_slist_iterator<T, const T&, const T*>	const_iterator;
		typedef _cppcds_slist_iterator<T, ref, ptr>				self;

		typedef T		value_type;
		typedef ref		reference;
		typedef ptr		pointer;

		typedef _cppcds_slist_node<T> node;

		_cppcds_slist_iterator(node* x):_cppcds_slist_iterator_base(x){}
		_cppcds_slist_iterator():_cppcds_slist_iterator_base(0){}
		_cppcds_slist_iterator(const iterator& x):_cppcds_slist_iterator_base(x.node){}

		reference operator*()const{return ((node*)_b_node)->data;}
		pointer operator->()const{return &(operator*());}

		// ++a;
		self& operator++()
		{
			_b_incr();
			return *this;
		}

		// a++
		self operator++(int)
		{
			self temp = *this;
			_b_incr();
			return temp;
		}
	};

	template<class T, class Alloc = alloc>
	class _cppcds_slist
	{
	public:
		typedef T					value_type;
		typedef value_type*			pointer;
		typedef const value_type*	const_pointer;
		typedef value_type&			reference;
		typedef const value_type	const_reference;
		typedef size_t				size_type;
		typedef ptrdiff_t			difference_type;

		typedef _cppcds_slist_iterator<T, T&, T*>				iterator;
		typedef _cppcds_slist_iterator<T, const T&, const T*>	const_iterator;

	private:
		typedef _cppcds_slist_node<T>				_cppcds_slist_node;
		typedef _cppcds_slist_node_base				_cppcds_slist_base_node;
		typedef _cppcds_slist_iterator_base			_cppcds_slist_iterator_base;

		typedef simple_alloc<_cppcds_slist_node, Alloc> _cppcds_slist_node_allocate;

		static _cppcds_slist_node* _cppcds_create_node(const value_type& x)
		{
			// 先分配好内存，然后在构造对象。
			_cppcds_slist_node* node = _cppcds_slist_node_allocate::allocate();
			cppcds_construct(&node->data, x);

			node->next = NULL;
			return node;
		}

		static void _cppcds_destory_node(_cppcds_slist_node* node)
		{
			// 先析构对象，在分配内存
			cppcds_destory(node);
			_cppcds_slist_node_allocate::deallocate(node);
		}

		static void _cppcds_destory_slist(_cppcds_slist_node* node)
		{
			_cppcds_slist_node* tmp;
			while (node)
			{
				tmp = (_cppcds_slist_node*)node->next;
				_cppcds_destory_node(node);
				node = tmp;
			}
		}

		// 清空slist，调用了_cppcds_destory_slist
		void _cppcds_slist_clear()
		{
			_cppcds_slist_node* node = (_cppcds_slist_node*)head.next;
			_cppcds_destory_slist(node);
		}
	private:
		_cppcds_slist_node_base head;
	public:
		// slist 构造函数和析构函数
		_cppcds_slist(){head.next = NULL;}
		~_cppcds_slist(){_cppcds_slist_clear();}

		iterator begin()
		{
			return iterator(((_cppcds_slist_node*)head.next));
		}

		iterator end()
		{
			return iterator(0);		// nice !_!
		}

		bool empty() const
		{
			return head.next == 0;
		}
		void push_front(const value_type& x)
		{
			_cppcds_make_link(&head, _cppcds_create_node(x));
		}

		void pop_front()
		{
			_cppcds_slist_node* node = (_cppcds_slist_node*)head.next;
			head.next = node->next;
			_cppcds_destory_node(node);
		}

		// 取得slist的第一个节点的值
		reference front() const
		{
			return ((_cppcds_slist_node*)head.next)->data;
		}

		// slist的大小
		size_type size()const
		{
			return _cppcds_slist_size(head.next);
		}

	};

}	// 命名空间结尾

#endif