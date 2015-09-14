#include "cppcds_vector_test.h"
#include "High_Time.h"
#include <vector>

void cppcds_vector_test()
{
	High_Timer time_Test;
	time_Test.Start();
	cppcds::cppcds_vector<int> cvi;
	cvi.reserve(100000000);
	cout << cvi.size() << endl;
	cout << cvi.capacity() << endl;
	for(int i = 1; i < 100000000; ++i)
	{
		cvi.push_back(i);
	}
	cout << *cvi.begin() << endl;
	time_Test.End();
	cout << "cppcds using time£º" << time_Test.Timer() << endl;

	time_Test.Start();
	std::vector<int> cvii;
	cvii.reserve(100000000);
	for(int i = 1; i < 100000000; ++i)
	{
		cvii.push_back(i);
	}
	cout << *cvii.begin() << endl;
	time_Test.End();
	cout << "std using time£º" << time_Test.Timer() << endl;
}