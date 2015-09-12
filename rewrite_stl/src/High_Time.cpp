//�߾��ȼ�ʱ��
//2010.11.11
//vs2005
#include "High_Time.h"
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void High_Timer::Start()
{
	QueryPerformanceCounter(&TimeStart);    //��ʱ��ʼ
}

void High_Timer::End()
{
	QueryPerformanceCounter(&TimeEnd);    //��ʱ����
}
///////////////////////////////////////////////////////////
double High_Timer::Timer()
{
	static double Freq;//��ʱ��Ƶ��
	static bool getfreq = false;
	if (!getfreq)//��ü�ʱ��Ƶ�ʣ�ֻ����һ��
	{
		LARGE_INTEGER f;
		if (QueryPerformanceFrequency(&f))
			Freq = f.QuadPart;
		else
			throw "�޷���ö�ʱ��Ƶ��";
		getfreq = true;
	}
	return (TimeEnd.QuadPart - TimeStart.QuadPart) / Freq;
}
