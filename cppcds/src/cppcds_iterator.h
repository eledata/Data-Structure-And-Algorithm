#ifndef _CPPCDS_ITERATOR_H_
#define _CPPCDS_ITERATOR_H_

namespace cppcds
{
	// 迭代器的适配器
	//template <class Container>
	//class back_insert_iterator
	//{
	//protected:
	//	Container* container;
	//public:
	//	typedef Container				container_type;
	//	typedef output_iterator_tag		iterator_category;
	//	typedef void					value_type;
	//	typedef void					difference_type;
	//	typedef void					pointer;
	//	typedef void					reference;

	//	explicit back_insert_iterator(Container& x):container(&x){}

	//	// 这样就规定了使用该迭代器的容器就要用value_type
	//	// 下面是重载操作符
	//	back_insert_iterator<Container>& operator=(const typename Container::value_type& value)
	//	{
	//		this->container->push_back(value);	// 说明这个容器具有push_back，那么才能使用这个迭代器
	//		return *this;
	//	}

	//	back_insert_iterator<Container>& operator*(){return *this;}
	//	back_insert_iterator<Container>& operator++(){return *this;}
	//	back_insert_iterator<Container>& operator++(int){return *this;}
	//};


	// cppcds_ostream_iterator的实现方法
	//template <class T>
	//class cppcds_ostream_iterator
	//{
	//protected:
	//	typedef std::ostream ostream;
	//	ostream cppcds_stream;
	//	const char *cppcds_string;

	//public:
	//	typedef output_iterator_tag iterator_category;
	//	typedef void				value_type;
	//	typedef void				distance_type;
	//	typedef void				pointer;
	//	typedef void				reference;

	//	cppcds_ostream_iterator(ostream& stream):cppcds_stream(stream), cppcds_string(0){}
	//	cppcds_ostream_iterator(ostream& stream, const char* value):cppcds_stream(stream), cppcds_string(value){}

	//	// 这个在copy()中比较的经常的使用的到
	//	cppcds_ostream_iterator<T>& operator=(const T& value)
	//	{
	//		cppcds_stream << value;
	//		if (cppcds_string)
	//		{
	//			cppcds_stream << cppcds_string;
	//		}
	//		return *this;
	//	}

	//	// 如果不能理解，那么就在copy函数找感觉
	//	cppcds_ostream_iterator<T>& operator*(){return *this;}
	//	cppcds_ostream_iterator<T>& operator++(){return *this;}
	//	cppcds_ostream_iterator<T>& operator++(int){return *this;}
	//};
}	// 命名空间结尾
#endif