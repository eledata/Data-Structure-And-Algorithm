#ifndef _CPPCDS_ITERATOR_H_
#define _CPPCDS_ITERATOR_H_

namespace cppcds
{
	// ��������������
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

	//	// �����͹涨��ʹ�øõ�������������Ҫ��value_type
	//	// ���������ز�����
	//	back_insert_iterator<Container>& operator=(const typename Container::value_type& value)
	//	{
	//		this->container->push_back(value);	// ˵�������������push_back����ô����ʹ�����������
	//		return *this;
	//	}

	//	back_insert_iterator<Container>& operator*(){return *this;}
	//	back_insert_iterator<Container>& operator++(){return *this;}
	//	back_insert_iterator<Container>& operator++(int){return *this;}
	//};


	// cppcds_ostream_iterator��ʵ�ַ���
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

	//	// �����copy()�бȽϵľ�����ʹ�õĵ�
	//	cppcds_ostream_iterator<T>& operator=(const T& value)
	//	{
	//		cppcds_stream << value;
	//		if (cppcds_string)
	//		{
	//			cppcds_stream << cppcds_string;
	//		}
	//		return *this;
	//	}

	//	// ���������⣬��ô����copy�����Ҹо�
	//	cppcds_ostream_iterator<T>& operator*(){return *this;}
	//	cppcds_ostream_iterator<T>& operator++(){return *this;}
	//	cppcds_ostream_iterator<T>& operator++(int){return *this;}
	//};
}	// �����ռ��β
#endif