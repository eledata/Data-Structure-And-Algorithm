#ifndef _CPPCDS_DEQUE_H_
#define _CPPCDS_DEQUE_H_

namespace cppcds
{
	// deque�����������Ĵ�С
	inline size_t cppcds_deque_buffer_size(size_t size)
	{
		return size < 512 ? size_t(512/size):size_t(1);
	}

	// deque��iterator
	template<class T, class ref, class ptr>
	struct cppcds_deque_iterator
	{
		typedef cppcds_deque_iterator<T, T&, T*>				iterator;
		typedef cppcds_deque_iterator<T, const T&, const T*>	const_iterator;
		typedef cppcds_deque_iterator<T, ref, ptr>				self;

		typedef T		value_type;
		typedef ref		reference;
		typedef ptr		pointer;
		typedef random_access_iterator_tag iterator_category;	// deque�ĵ�������
		typedef size_t	size_type;
		typedef T**		map_pointer;		// �п�����
		typedef ptrdiff_t difference_type;

		// �������Ĵ�С
		static size_t buffer_size()
		{
			return cppcds_deque_buffer_size(sizeof(T));
		}
		
		// �������Ľṹ
		T* current;			// ָ�򻺳��������е�Ԫ��
		T* first;			// ��������ͷ��ַ
		T* last;			// ��������β��ַ
		map_pointer map_node;	// �п����еĽڵ㣬����ڵ�ָ�򻺳���
	
		// ���캯��
		cppcds_deque_iterator(T* x, map_pointer y):current(x), first(*y), last(*y + buffer_size()), map_node(y){}
		cppcds_deque_iterator():current(0), first(0), last(0), map_node(0){}
		cppcds_deque_iterator(){}
		cppcds_deque_iterator(const iterator& x):current(x.current), first(x.first), last(x.last), map_node(x.map_node){}

		// operator��showtime
		// �����operator*, ->, -, ++, --
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

		// �ұ���ǰ�ߵ����
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
			++(*this);	// ����Ѿ���������������
			return temp;
		}

		self& operator--()
		{
			--current;
			if (current == first)
			{
				// �����ߵ�������п��������м�
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
			// current - first�� ���ڵ�λ�á� ��n֮�����Ҫ��ǰ���ľ���
			difference_type dis = n + difference_type(current - first);

			if (dis <  buffer_size() && dis >= 0)
			{
				current = current + n;
			} 
			else
			{
				// -dis - 1:��Ϊ�����������䷶Χ�ǣ�0-buffer_size() -1;
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

		// ������һ������������ʼλ��
		void set_node(map_pointer new_node)
		{
			map_node = new_node;	
			first = *new_node;		// *new_node,��һ�����������׵�ַ
			last = first + difference_type(buffer_size());
		}
	};

	template<class T, class Alloc = alloc>
	class cppcds_deque
	{
	public:	
		// ��������
		typedef T						value_type;
		typedef value_type*				pointer_type;
		typedef const value_type*		const_pointer_type;
		typedef value_type&				reference;
		typedef const value_type&		const_reference;
		typedef size_t					size_type;
		typedef ptrdiff_t				difference_type;
		typedef T**						map_pointer;

		// ������
		typedef cppcds_deque_iterator<T, T&, T*>				iterator;
		typedef cppcds_deque_iterator<T, const T&, const T*>	const_iterator;

	private:
		// �ڴ����
		typedef simple_alloc<T, Alloc> deque_node_allocate;
		typedef simple_alloc<T*, Alloc> deque_map_allocate;

		// �������Ĵ�С
		static size_t buffer_size()
		{
			return cppcds_deque_buffer_size(sizeof(T));
		}

		// ���仺����
		pointer_type cppcds_deque_node_allocate()
		{
			return deque_node_allocate::allocate(buffer_size(sizeof(T)))
		}

		// ���ٻ�����
		void cppcds_deque_node_deallocate(pointer_type p)
		{
			deque_node_allocate::deallocate(p, buffer_size(sizeof(T)))
		}

		// �����п���
		map_pointer cppcds_deque_map_allocate(size_type n)
		{
			return deque_map_allocate::allocate(n);
		}

		// �����п���
		void cppcds_deque_map_deallocate(map_pointer p, size_type n)
		{
			deque_node_allocate::deallocate(p, n)
		}

	private:
		// �п���������
		map_pointer map;
		size_type	map_size;
		iterator	start;
		iterator	finish;

		// �п����ĳ�ʼ��С
		enum { initial_map_size = 8 };

		// �����п���
		void initialize_map(size_type size);
		void create_nodes(map_pointer nodestart, map_pointer nodefinish);
		void destory_nodes(map_pointer nodestart, map_pointer nodefinish);

		// fill_initialize
		void fill_initialize(size_type size, const value_type& value);

	public:
		// ���캯��
		cppcds_deque():map_node(0), map_size(0), start(0), finish(0){}
		cppcds_deque(size_type n)
		{
			fill_initialize(n, 0);
		}



		// ��������
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
		// ���������ĸ�������
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
		// �����п����Ĵ�С����
		size_type node_num = size/buffer_size() + 1;
		map_size = cppcds_max((size_type)initial_map_size, node_num + 2);
		map = cppcds_deque_map_allocate(map_size);

		map_pointer nodestart = map + (map_size - node_num)/2;
		map_pointer nodefinish = nodestart + node_num;

		// ����size�������������Ĵ�С
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

	// ���������ĸ�������
	template<class T, class Alloc>
	void cppcds_deque<T, Alloc>::push_back_aux(const value_type& value)
	{
		   
	}
}
#endif