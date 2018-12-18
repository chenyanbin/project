#ifndef __DictSignReward__
#define __DictSignReward__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictSignReward:public Ref
{
public:
	DictSignReward():	
	id(0)//ID		
	,day(0)//天数		
	,itemId(0)//物品编号		
	,itemName("")//物品名称		
	,itemType(0)//物品类型		
	,itemNumber(0)//物品数量		
	,isDouble(0)//是否双倍		
	,vipLevel(0)//vip等级条件		
	{};

	short id;
	short day;
	int itemId;
	string itemName;
	int itemType;
	int itemNumber;
	short isDouble;
	short vipLevel;
};
#endif
