#include "cppcds_iterator_test.h"

void cppcds_iterator_test()
{
	int testarr[] = {1, 2, 4, 5, 6, 77, 7, 65};
	cppcds::_cppcds_list<int> lt;
	cppcds::_cppcds_list<int> lt1;

	for (int i = 10; i > 1; --i)
	{
		lt.push_front(i);
	}

	for (int i = 15; i > 11; --i)
	{
		lt1.push_front(i);
	}

	cppcds::_cppcds_list<int>::iterator ite;
	ite = lt.begin();
	cout << cppcds::distance(testarr, testarr + 5) << endl;
	cppcds::advance(ite, 1);
	cout << *ite << endl;
}