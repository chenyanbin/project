#ifndef __DictHeroPrestigeUpCost__
#define __DictHeroPrestigeUpCost__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictHeroPrestigeUpCost:public Ref
{
public:
	DictHeroPrestigeUpCost():	
	id(0)//ID		
	,level(0)//历练者等级		
	,quality(0)//被吞噬者品质		
	,consumeCoin(0)//花费铜钱		
	,rewardExp(0)//被吞噬者提供经验		
	{};

	int id;
	short level;
	int quality;
	int consumeCoin;
	int rewardExp;
};
#endif
