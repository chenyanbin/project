#ifndef __DictLegendRank__
#define __DictLegendRank__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictLegendRank:public Ref
{
public:
	DictLegendRank():	
	id(0)//ID		
	,rankmin(0)//名次下限		
	,rankmax(0)//名次上限		
	,honor(0)//军功奖励		
	,coin(0)//铜钱奖励		
	,item1Type(0)//物品1类型		
	,itemId1(0)//物品1ID		
	,item1Number(0)//物品1数量		
	,hero1Prestige(0)//武将1声望		
	,item2Type(0)//物品2类型		
	,itemId2(0)//物品2ID		
	,item2Number(0)//物品2数量		
	,hero2Prestige(0)//武将2声望		
	,item3Type(0)//物品3类型		
	,itemId3(0)//物品3ID		
	,item3Number(0)//物品3数量		
	,hero3Prestige(0)//武将3声望		
	,item4Type(0)//物品4类型		
	,itemId4(0)//物品4ID		
	,item4Number(0)//物品4数量		
	,hero4Prestige(0)//武将4声望		
	{};

	short id;
	int rankmin;
	int rankmax;
	int honor;
	int coin;
	int item1Type;
	int itemId1;
	short item1Number;
	short hero1Prestige;
	int item2Type;
	int itemId2;
	short item2Number;
	short hero2Prestige;
	int item3Type;
	int itemId3;
	short item3Number;
	short hero3Prestige;
	int item4Type;
	int itemId4;
	short item4Number;
	short hero4Prestige;
};
#endif
