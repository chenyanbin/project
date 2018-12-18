#ifndef __DictBlackshopResetCost__
#define __DictBlackshopResetCost__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictBlackshopResetCost:public Ref
{
public:
	DictBlackshopResetCost():	
	id(0)//编号		
	,resetTimes(0)//刷新次数		
	,gold(0)//花费元宝		
	,time(0)//保持倒计时(秒)		
	{};

	int id;
	short resetTimes;
	int gold;
	int time;
};
#endif
