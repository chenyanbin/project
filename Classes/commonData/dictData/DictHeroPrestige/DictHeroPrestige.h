#ifndef __DictHeroPrestige__
#define __DictHeroPrestige__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictHeroPrestige:public Ref
{
public:
	DictHeroPrestige():	
	level(0)//声望等级		
	,levelUpNeed(0)//升级所需卡牌		
	,lootUp1(0)//副本第一次声望翻牌掉率加成		
	,lootUp2(0)//副本第二次声望翻牌掉率加成		
	,lootUp3(0)//副本第三次声望翻牌掉率加成		
	{};

	short level;
	short levelUpNeed;
	short lootUp1;
	short lootUp2;
	short lootUp3;
};
#endif
