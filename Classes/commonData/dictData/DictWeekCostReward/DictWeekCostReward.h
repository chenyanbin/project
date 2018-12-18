#ifndef __DictWeekCostReward__
#define __DictWeekCostReward__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictWeekCostReward:public Ref
{
public:
	DictWeekCostReward():	
	id(0)//ID		
	,day(0)//天数		
	,charge(0)//累计花费		
	,itemId(0)//物品编号		
	,itemName("")//物品名称		
	,itemType(0)//物品类型		
	,itemNumber(0)//物品数量		
	{};

	short id;
	short day;
	int charge;
	int itemId;
	string itemName;
	int itemType;
	int itemNumber;
};
#endif
