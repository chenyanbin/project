#ifndef __DictBattleRebornCost__
#define __DictBattleRebornCost__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictBattleRebornCost:public Ref
{
public:
	DictBattleRebornCost():	
	rebornTimes(0)//接关次数		
	,gold(0)//花费元宝		
	{};

	short rebornTimes;
	int gold;
};
#endif
