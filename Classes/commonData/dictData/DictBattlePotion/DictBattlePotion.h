#ifndef __DictBattlePotion__
#define __DictBattlePotion__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictBattlePotion:public Ref
{
public:
	DictBattlePotion():	
	vipLevel(0)//vip等级		
	,potionTimes(0)//药水购买次数		
	{};

	short vipLevel;
	short potionTimes;
};
#endif
