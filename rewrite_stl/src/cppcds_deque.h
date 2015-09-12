#ifndef _CPPCDS_DEQUE_H_
#define _CPPCDS_DEQUE_H_

namespace cppcds
{
	// deque单个缓冲区的大小
	inline size_t cppcds_deque_buffer_size(size_t size)
	{
		return size < 512 ? size_t(512/size):size_t(1);
	}

	// deque的iterator
	template<class T, class ref, class ptr>
	struct cppcds_deque_iterator
	{
		typedef cppcds_deque_iterator<T, T&, T*>				iterator;
		typedef cppcds_deque_iterator<T, const T&, const T*>	const_iterator;
		typedef cppcds_deque_iterator<T, ref, ptr>				self;

		typedef T		value_type;
		typedef ref		reference;
		typedef ptr		pointer;
		typedef random_access_iterator_tag iterator_category;	// deque的迭代类型
		typedef size_t	size_type;
		typedef T**		map_pointer;		// 中控中心
		typedef ptrdiff_t difference_type;

		// 缓冲区的大小
		static size_t buffer_size()
		{
			return cppcds_deque_buffer_size(sizeof(T));
		}
		
		// 缓冲区的结构
		T* current;			// 指向缓冲区中现行的元素
		T* first;			// 缓冲区的头地址
		T* last;			// 缓冲区的尾地址
		map_pointer map_node;	// 中控区中的节点，这个节点指向缓冲区
	
		// 构造函数
		cppcds_deque_iterator(T* x, map_pointer y):current(x), first(*y), last(*y + buffer_size()), map_node(y){}
		cppcds_deque_iterator():current(0), first(0), last(0), map_node(0){}
		cppcds_deque_iterator(){}
		cppcds_deque_iterator(const iterator& x):current(x.current), first(x.first), last(x.last), map_node(x.map_node){}

		// operator的showtime
		// 神奇的operator*, ->, -, ++, --
		reference operator*()const
		{
			return *current;
		}

		pointer operator->() const
		{
			return current;
		}

		difference_type operator-(const self& x)
		{
			return difference_type(buffer_size())*(map_node - x.map_node - 1) + (current - first) + (x.last - x.current);
		}

		// 右边往前走的情况
		self& operator++()
		{
			++current;
			if (current == last)
			{
				set_node(map_node + 1);
				current = first;
			}

			return *this;
		}

		self operator++(int)
		{
			self temp = *this;
			++(*this);	// 这个已经包含了上面的情况
			return temp;
		}

		self& operator--()
		{
			--current;
			if (current == first)
			{
				// 往左走的情况，中控器在在中间
				set_node(map_node - 1);
				current = last;
			}

			return *this;
		}

		self operator--(int)
		{
			self temp = *this;
			--(*this);
			return temp;
		}

		self& operator+=(difference_type n)
		{
			// current - first， 现在的位置。 加n之后就是要向前跳的距离
			difference_type dis = n + difference_type(current - first);

			if (dis <  buffer_size() && dis >= 0)
			{
				current = current + n;
			} 
			else
			{
				// -dis - 1:因为缓冲区的区间范围是：0-buffer_size() -1;
				difference_type node_dis = dis > 0 ? dis/buffer_size(): -difference_type((-dis - 1)/buffer_size()) - 1;
				set_node(map_node + node_dis);
				current = first + (dis - node_dis*difference_type(buffer_size()));
			}
			return *this;
		}

		self operator+(difference_type n)
		{
			self temp = *this;
			return temp += n;
		}

		self& operator-=(difference_type n)
		{
			return *this += (-n);
		}

		self operator-(difference_type n)
		{
			self temp = *this;
			return temp -= n;
		}

		reference operator[](difference_type n)
		{
			return *(*this + n);
		}

		bool operator==(const self& x)const
		{
			return current == x.current;
		}

		bool operator!=(const self& x)const
		{
			return !(*this == x);
		}

		bool operator<(const self& x) const
		{
			return map_node == x.map_node ? (current < x.current):(map_node < x.map_node);
		}

		bool operator>(const self& x) const
		{
			return x < *this;
		}

		bool operator<=(const self& x)const
		{
			return !(x < *this);
		}

		bool operator>=(const self& x) const
		{
			return !(*this < x);
		}

		// 设置下一个缓冲区的起始位置
		void set_node(map_pointer new_node)
		{
			map_node = new_node;	
			first = *new_node;		// *new_node,下一个缓冲区的首地址
			last = first + difference_type(buffer_size());
		}
	};

	template<class T, class Alloc = alloc>
	class cppcds_deque
	{
	public:	
		// 基本类型
		typedef T						value_type;
		typedef value_type*				pointer_type;
		typedef const value_type*		const_pointer_type;
		typedef value_type&				reference;
		typedef const value_type&		const_reference;
		typedef size_t					size_type;
		typedef ptrdiff_t				difference_type;
		typedef T**						map_pointer;

		// 迭代器
		typedef cppcds_deque_iterator<T, T&, T*>				iterator;
		typedef cppcds_deque_iterator<T, const T&, const T*>	const_iterator;

	private:
		// 内存分配
		typedef simple_alloc<T, Alloc> deque_node_allocate;
		typedef simple_alloc<T*, Alloc> deque_map_allocate;

		// 缓冲区的大小
		static size_t buffer_size()
		{
			return cppcds_deque_buffer_size(sizeof(T));
		}

		// 分配缓冲区
		pointer_type cppcds_deque_node_allocate()
		{
			return deque_node_allocate::allocate(buffer_size(sizeof(T)))
		}

		// 销毁缓冲区
		void cppcds_deque_node_deallocate(pointer_type p)
		{
			deque_node_allocate::deallocate(p, buffer_size(sizeof(T)))
		}

		// 分配中控区
		map_pointer cppcds_deque_map_allocate(size_type n)
		{
			return deque_map_allocate::allocate(n);
		}

		// 销毁中控区
		void cppcds_deque_map_deallocate(map_pointer p, size_type n)
		{
			deque_node_allocate::deallocate(p, n)
		}

	private:
		// 中控区的声明
		map_pointer map;
		size_type	map_size;
		iterator	start;
		iterator	finish;

		// 中控区的初始大小
		enum { initial_map_size = 8 };

		// 建立中控区
		void initialize_map(size_type size);
		void create_nodes(map_pointer nodestart, map_pointer nodefinish);
		void destory_nodes(map_pointer nodestart, map_pointer nodefinish);

		// fill_initialize
		void fill_initialize(size_type size, const value_type& value);

	public:
		// 构造函数
		cppcds_deque():map_node(0), map_size(0), start(0), finish(0){}
		cppcds_deque(size_type n)
		{
			fill_initialize(n, 0);
		}



		// 操作函数
		void push_back(const value_type& value)
		{
			if (finish.current != finish.last - 1)
			{
				cppcds_construct(finish.current, value);
				++finish.current;
			} 
			else
			{
				push_back_aux(value);
			}
		}

	private:
		// 操作函数的辅助函数
		push_back_aux(const value_type& value);
	};

	template<class T, class Alloc>
	void cppcds_deque<T, Alloc>::create_nodes(map_pointer nodestart, map_pointer nodefinish)
	{
		map_pointer temp = NULL;

		for (temp = nodestart; temp < nodefinish; ++temp)
		{
			*temp = cppcds_deque_node_allocate();
		}
	}

	template<class T, class Alloc>
	void cppcds_deque<T, Alloc>::initialize_map(size_type size)
	{
		// 处理中控区的大小问题
		size_type node_num = size/buffer_size() + 1;
		map_size = cppcds_max((size_type)initial_map_size, node_num + 2);
		map = cppcds_deque_map_allocate(map_size);

		map_pointer nodestart = map + (map_size - node_num)/2;
		map_pointer nodefinish = nodestart + node_num;

		// 根据size来创建缓冲区的大小
		create_nodes(nodestart, nodefinish);

		start.set_node(nodestart);
		finish.set_node(nodefinish - 1);
		start.current = start.first;
		finish.current = finish.first + size%buffer_size();

	}

	template<class T, class Alloc>
	void cppcds_deque<T, Alloc>::fill_initialize(size_type size, const value_type& value)
	{
		map_pointer temp = NULL;

		for (temp = start.map_node; temp < finish.map_node; ++temp)
		{
			cppcds_uninitialized_fill(*temp, *temp + buffer_size(), value);
		}

		cppcds_uninitialized_fill(finish.first, finish.current, value);
	}

	// 操作函数的辅助函数
	template<class T, class Alloc>
	void cppcds_deque<T, Alloc>::push_back_aux(const value_type& value)
	{
		   
	}
}
#endif