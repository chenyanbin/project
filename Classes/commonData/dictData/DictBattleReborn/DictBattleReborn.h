#ifndef __DictBattleReborn__
#define __DictBattleReborn__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictBattleReborn:public Ref
{
public:
	DictBattleReborn():	
	vipLevel(0)//vip等级		
	,rebornTimes(0)//接关次数		
	{};

	short vipLevel;
	short rebornTimes;
};
#endif
