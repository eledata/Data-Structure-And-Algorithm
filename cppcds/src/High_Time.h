//�߾��ȼ�ʱ��
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
	void Start();//��ʱ��ʼ
	void End();//��ʱ���� 
	double Timer();//����ʱ��
};

////////////////////////////////////////////////////////
#endif