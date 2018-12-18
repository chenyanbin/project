#ifndef __DictBattlePotionCost__
#define __DictBattlePotionCost__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictBattlePotionCost:public Ref
{
public:
	DictBattlePotionCost():	
	potionTimes(0)//药水购买次数		
	,gold(0)//花费元宝		
	{};

	short potionTimes;
	int gold;
};
#endif
