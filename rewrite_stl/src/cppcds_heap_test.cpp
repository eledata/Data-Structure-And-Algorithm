#include "cppcds_heap_test.h"

using namespace cppcds;
void cppcds_heap_test()
{
	int testarr[15] = {0, 1, 2, 3, 4, 5, 6, 7, };
	for(int i = 0; i < 8; ++i)
	{
		cout << testarr[i] << " ";
	}
		cout << endl;
	make_heap(testarr, testarr + 8);


	for(int i = 0; i < 8; ++i)
	{
		cout << testarr[i] << " ";
	}
	cout << endl;
	testarr[8] = 16;
	push_heap(testarr, testarr + 9);
	for(int i = 0; i < 9; ++i)
	{
		cout << testarr[i] << " ";
	}
}