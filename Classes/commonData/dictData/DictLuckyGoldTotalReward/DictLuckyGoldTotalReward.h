#ifndef __DictLuckyGoldTotalReward__
#define __DictLuckyGoldTotalReward__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictLuckyGoldTotalReward:public Ref
{
public:
	DictLuckyGoldTotalReward():	
	id(0)//ID		
	,time(0)//点击次数		
	,itemId(0)//物品编号		
	,itemName("")//物品名称		
	,itemType(0)//物品类型		
	,itemNumber(0)//物品数量		
	{};

	short id;
	short time;
	int itemId;
	string itemName;
	int itemType;
	int itemNumber;
};
#endif
