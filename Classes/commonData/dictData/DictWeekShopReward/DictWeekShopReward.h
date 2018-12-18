#ifndef __DictWeekShopReward__
#define __DictWeekShopReward__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictWeekShopReward:public Ref
{
public:
	DictWeekShopReward():	
	id(0)//ID		
	,day(0)//天数		
	,itemId(0)//物品编号		
	,itemName("")//物品名称		
	,itemType(0)//物品类型		
	,itemNumber(0)//物品数量		
	,cost(0)//原价		
	,costCheap(0)//惊爆价		
	,buyNum(0)//可购买人数		
	,baseNum(0)//人数基数		
	,startTimes(0)//低数值倍数		
	,timesCancelNum(0)//倍数取消人数		
	{};

	short id;
	short day;
	int itemId;
	string itemName;
	int itemType;
	int itemNumber;
	int cost;
	int costCheap;
	short buyNum;
	short baseNum;
	double startTimes;
	short timesCancelNum;
};
#endif
