#include "cppcds_list_test.h"

using namespace  cppcds;

void cppcds_list_test()
{
	_cppcds_list<int> lt;
	_cppcds_list<int> lt1;

	for (int i = 10; i > 1; --i)
	{
		lt.push_front(i);
	}
	cout << lt.size() << endl;

	/*for (int i = 15; i > 11; --i)
	{
		lt1.push_front(i);
	}

	_cppcds_list<int>::iterator ite;
	ite = lt.begin();
	for (; ite != lt.end(); ++ite)
	{
		cout << *ite << " ";
	}
	cout << endl;
	_cppcds_list<int>::iterator::iterator ite1;
	_cppcds_list<int>::iterator::iterator ite2;
	ite1 = lt.begin();


	lt.reverse();
	lt.splice(++ite1, lt1);

	cout << lt.size() << endl;

	ite2 = lt.begin();
	for (; ite2 != lt.end(); ++ite2)
	{
		cout << *ite2 << " ";
	}
	cout << endl;*/
}