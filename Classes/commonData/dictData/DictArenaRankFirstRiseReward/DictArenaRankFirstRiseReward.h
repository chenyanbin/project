#ifndef __DictArenaRankFirstRiseReward__
#define __DictArenaRankFirstRiseReward__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictArenaRankFirstRiseReward:public Ref
{
public:
	DictArenaRankFirstRiseReward():	
	id(0)//ID		
	,rankMax(0)//名次上限		
	,rankMin(0)//名次下限		
	,goldCoefficient(0)//元宝系数		
	,type(0)//物品类型		
	,itemId(0)//物品ID		
	{};

	int id;
	int rankMax;
	int rankMin;
	int goldCoefficient;
	int type;
	int itemId;
};
#endif
