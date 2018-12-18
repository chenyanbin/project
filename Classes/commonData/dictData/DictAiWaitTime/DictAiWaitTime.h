#ifndef __DictAiWaitTime__
#define __DictAiWaitTime__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictAiWaitTime:public Ref
{
public:
	DictAiWaitTime():	
	ID(0)//编号		
	,desc("")//备注		
	,waitTime1(0)//等待时间1		
	,wtRate1(0)//等待时间权重1		
	,waitTime2(0)//等待时间2		
	,wtRate2(0)//等待时间权重2		
	,waitTime3(0)//等待时间3		
	,wtRate3(0)//等待时间权重3		
	,waitTime4(0)//等待时间4		
	,wtRate4(0)//等待时间权重4		
	,waitTime5(0)//等待时间5		
	,wtRate5(0)//等待时间权重5		
	{};

	int ID;
	string desc;
	int waitTime1;
	int wtRate1;
	int waitTime2;
	int wtRate2;
	int waitTime3;
	int wtRate3;
	int waitTime4;
	int wtRate4;
	int waitTime5;
	int wtRate5;
};
#endif
