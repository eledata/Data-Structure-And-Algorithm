#include "cppcds_pair_test.h"

using namespace cppcds;
void cppcds_pair_test()
{
	_cppcds_pair<int, int> pii;
	_cppcds_pair<int, int> pii1;
	pii = cppcds::make_pair(5, 6);
	pii1 = cppcds::make_pair(5, 6);
	
	cout << pii.first << " " << pii.second << endl;

	cout << (pii == pii1) << endl;
	cout << (pii < pii1) << endl;
}