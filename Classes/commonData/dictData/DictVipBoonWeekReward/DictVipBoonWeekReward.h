#ifndef __DictVipBoonWeekReward__
#define __DictVipBoonWeekReward__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictVipBoonWeekReward:public Ref
{
public:
	DictVipBoonWeekReward():	
	id(0)//ID		
	,vipLevel(0)//VIP等级		
	,itemId(0)//物品编号		
	,itemName("")//物品名称		
	,itemType(0)//物品类型		
	,itemNumber(0)//物品数量		
	,cost(0)//原价		
	,costCheap(0)//惊爆价		
	{};

	short id;
	short vipLevel;
	int itemId;
	string itemName;
	int itemType;
	int itemNumber;
	int cost;
	int costCheap;
};
#endif
