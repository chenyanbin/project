#ifndef __DictLegendBattleTouch__
#define __DictLegendBattleTouch__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictLegendBattleTouch:public Ref
{
public:
	DictLegendBattleTouch():	
	stageBattleId(0)//战役ID		
	,monsterId(0)//对应BossID		
	{};

	int stageBattleId;
	int monsterId;
};
#endif
