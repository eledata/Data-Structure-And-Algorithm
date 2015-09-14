//高精度计时器
//2010.11.11
#ifndef HIGH_TIME
#define HIGH_TIME
////////////////////////////////////////////////////////
#include <windows.h>

class High_Timer
{
private:
	_LARGE_INTEGER TimeStart;
	_LARGE_INTEGER TimeEnd;
public:
	void Start();//计时开始
	void End();//计时结束 
	double Timer();//返回时差
};

////////////////////////////////////////////////////////
#endif