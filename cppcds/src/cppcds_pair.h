#ifndef _CPPCDS_PAIR_H_
#define _CPPCDS_PAIR_H_

namespace cppcds
{
	template <class T1, class T2>
	struct _cppcds_pair
	{
		typedef T1 first_type;
		typedef T2 second_type;

		T1 first;
		T2 second;

		_cppcds_pair():first(T1()), second(T2()){}
		_cppcds_pair(const T1& t1, const T2& t2):first(t1), second(t2){}

		template <class T1, class T2>
		friend bool operator==(const _cppcds_pair<T1, T2>& x, const _cppcds_pair<T1, T2>& y);

		template <class T1, class T2>
		friend bool operator<(const _cppcds_pair<T1, T2>& x, const _cppcds_pair<T1, T2> &y);

		template <class T1, class T2>
		friend _cppcds_pair<T1, T2> make_pair(const T1& x, const T2& y);
	};

	// 以下这几个函数都是_cppcds_pair自产自销的函数。
	template <class T1, class T2>
	inline 
	bool operator==(const _cppcds_pair<T1, T2>& x, const _cppcds_pair<T1, T2>& y)
	{
		return (x.first == y.first)&&(x.second == y.second);
	}

	template <class T1, class T2>
	inline 
	bool operator<(const _cppcds_pair<T1, T2>& x, const _cppcds_pair<T1, T2>& y)
	{
		return (x.first < y.first)||(!(x.first < y.first)&&(x.second < y.second));
	}

	template <class T1, class T2>
	inline
	_cppcds_pair<T1, T2> 
	make_pair(const T1& x, const T2& y)
	{
		return _cppcds_pair<T1, T2>(x, y);
	}

}	// 命名空间结尾

#endif