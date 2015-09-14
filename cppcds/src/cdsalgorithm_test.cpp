#include "cdsalgorithm_test.h"

using namespace cppcds;

void print(int& elem)
{
	cout << elem << endl;
}
void cdsalgorithm_test()
{
	//int a = 5;
	//int b = 9;

	//cppcds_swap(a, b);
	//cout << a << b << endl;
	//cout << cppcds_min(a, b) << cppcds_max(a, b) << endl;
	_cppcds_list<int> lt;
	_cppcds_list<int> lt1;
	cout << endl;

	for (int i = 10; i > 1; --i)
	{
		lt.push_front(i);
	}


	for (int i = 20; i > 10; --i)
	{
		lt1.push_front(i);
	}

	_cppcds_list<int>::iterator ltt1, ltt2, ltt3;
	ltt1 = lt.begin();
	ltt3 = lt.end();
	ltt2 = lt1.begin();
	
	//cout << *ltt2 << *ltt1 << endl;
	//cppcds_iter_swap(ltt1, ltt2);
	//cout << *ltt2 << *ltt1 << endl;
	//int A[10] = {1,2,3,4,5,};
	//int B[15] = {5,6,7,8,8,};

	//cppcds_copy(A, A+3, B);
	//cout << *B << endl;

}