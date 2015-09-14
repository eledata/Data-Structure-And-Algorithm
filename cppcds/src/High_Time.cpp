//高精度计时器
//2010.11.11
//vs2005
#include "High_Time.h"
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void High_Timer::Start()
{
	QueryPerformanceCounter(&TimeStart);    //计时开始
}

void High_Timer::End()
{
	QueryPerformanceCounter(&TimeEnd);    //计时结束
}
///////////////////////////////////////////////////////////
double High_Timer::Timer()
{
	static double Freq;//计时器频率
	static bool getfreq = false;
	if (!getfreq)//获得计时器频率，只运行一次
	{
		LARGE_INTEGER f;
		if (QueryPerformanceFrequency(&f))
			Freq = f.QuadPart;
		else
			throw "无法获得定时器频率";
		getfreq = true;
	}
	return (TimeEnd.QuadPart - TimeStart.QuadPart) / Freq;
}
