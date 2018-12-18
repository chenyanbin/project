#ifndef __DictArenaRankDayReward__
#define __DictArenaRankDayReward__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictArenaRankDayReward:public Ref
{
public:
	DictArenaRankDayReward():	
	id(0)//ID		
	,rankMax(0)//排名上限		
	,rankMin(0)//排名下限		
	,itemId1(0)//物品1ID		
	,type1(0)//物品1类型		
	,number1(0)//物品1数量		
	,itemId2(0)//物品2ID		
	,type2(0)//物品2类型		
	,number2(0)//物品2数量		
	{};

	int id;
	short rankMax;
	short rankMin;
	int itemId1;
	int type1;
	int number1;
	int itemId2;
	int type2;
	int number2;
};
#endif
