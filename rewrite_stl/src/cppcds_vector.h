#ifndef _CPPCDS_VECTOR_H_
#define _CPPCDS_VECTOR_H_

namespace cppcds
{
	template<class T, class Alloc = alloc>
	class cppcds_vector
	{
	public:
		typedef T						value_type;
		typedef value_type*				pointer;		// ����vectorά����һ�������Ŀռ䣬������Ԫ����Σ�
		typedef value_type*				iterator;		// ��ָͨ�������Ϊvector�ĵ��������������е�����
		typedef value_type&				reference;
		typedef const value_type*		const_pointer;
		typedef const value_type*		const_iterator;
		typedef const value_type&		const_reference;
		typedef size_t					size_type;
		typedef ptrdiff_t				difference_type;

	protected:
		// �ڴ���������������ǣ�
		typedef simple_alloc<value_type, Alloc> _cppcds_vector_allocate;

		iterator start;				// Ŀǰʹ�ÿռ��ͷ
		iterator finish;			// Ŀǰʹ�ÿռ��β
		iterator end_of_storage;	// Ŀǰ���ÿռ��β

		// �ڴ�����ĺ���
		iterator allocate(size_type n)
		{
			iterator start = _cppcds_vector_allocate::allocate(n);
			return start;
		}

		void deallocate()
		{
			if (start)
			{
				_cppcds_vector_allocate::deallocate(start, end_of_storage - start);
			}
		}

		iterator allocate_and_fill(size_type n, const value_type &value)
		{
			iterator result = allocate(n);
			cppcds_uninitialized_fill_n(result, n, value);
			return result;
		}

		iterator fill_and_initrialize(size_type n, const value_type &value)
		{
			iterator start = allocate_and_fill(n, value);
			finish = start;
			end_of_storage = start + n;
			return start;
		}

		iterator allocate_and_copy(size_type n, iterator first, iterator last)
		{
			iterator result = allocate(n);

			uninitialized_copy(first, last, result);
			return result;
		}

	protected:
		// ����Ԫ�صĸ������������������������
		void insert_aux(iterator position, const T& value);
		void insert_aux(iterator position);
	public:
		// ���캯��
		cppcds_vector():start(0), finish(0), end_of_storage(0){}
		cppcds_vector(size_type size, const T& value){fill_and_initrialize(size, value);}
		cppcds_vector(int size, const T& value){fill_and_initrialize(size, value);}
		cppcds_vector(long size, const T& value){fill_and_initrialize(size, value);}
		explicit cppcds_vector(size_type size){fill_and_initrialize(n, T());}

		// ��������
		~cppcds_vector()
		{

		}
		// ��������

		void reserve(size_type n)
		{
			if (capacity() < n)
			{
				const size_type old_size = size();
				iterator temp = allocate_and_copy(n, start, finish);
				
				cppcds_destory(start, finish);
				deallocate();
				cout << n << endl;
				start = temp;
				finish = temp + old_size;
				end_of_storage = start + n;
			}
		}

		void push_back(const T& value)
		{
			if (finish != end_of_storage)
			{
				cppcds_construct(finish, value);
				++finish;
			}
			else
			{
				insert_aux(end(), value);
			}
		}

		// begin, end, rbegin, rend
		iterator begin()
		{
			return start;
		}

		const_iterator begin() const
		{
			return start;
		}

		iterator end()
		{
			return finish;
		}

		const_iterator end() const
		{
			return finish;
		}

		// size max_size capacity empty
		size_type size() const
		{
			return size_type(finish - start);
		}

		//size_type max_size() const
		//{
		//	return end_of_storage - start;
		//}

		size_type capacity() const
		{
			return end_of_storage - finish;
		}

		bool empty() const
		{
			return (begin() == end());
		}

		// operator
		reference operator[](size_type n)
		{
			return *(begin() + n);
		}

		const_reference operator[](size_type n) const
		{
			return *(begin() + n);
		}


	};

	template <class T, class Alloc>
	void cppcds_vector<T, Alloc>::insert_aux(iterator position, const T& value)
	{
		if (finish != end_of_storage)
		{
			cppcds_construct(finish, *(finish - 1));
			++finish;
			T value_copy = value;
			cppcds_backward(position, finish - 2, finish - 1);
			*position = value_copy;
		} 
		else
		{
			 const size_type old_size = size();
			 // ����������˷���ı��ˡ�
			 const size_type len = old_size != 0 ? 2*old_size : 1;
			 iterator new_start = allocate(len);
			 iterator new_finish = new_start;

			 // ������try catch�������Ȳ���
			 new_finish = cppcds_uninitialized_copy(start, position, new_start);
			 cppcds_construct(new_finish, value);
			 ++new_finish;
			 new_finish = cppcds_uninitialized_copy(position, finish, new_finish);

			 cppcds_destory(start, finish);
			 deallocate();

			 start = new_start;
			 finish = new_finish;
			 end_of_storage = new_start + len;
		}
	}
}

#endif