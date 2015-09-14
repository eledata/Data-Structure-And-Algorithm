#ifndef _CPPCDS_FUNCTIONAL_H_
#define _CPPCDS_FUNCTIONAL_H_



// ֤ͬ����������ԭֵ
template <class T>
inline T cppcds_identity_element(cppcds_plus<T>)
{
	return T(0);
}

template <class T>
inline T cppcds_identity_element(cppcds_multiplies<T>)
{
	return T(1);
}

#endif