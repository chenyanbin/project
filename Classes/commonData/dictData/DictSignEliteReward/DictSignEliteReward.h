#ifndef __DictSignEliteReward__
#define __DictSignEliteReward__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictSignEliteReward:public Ref
{
public:
	DictSignEliteReward():	
	id(0)//ID		
	,day(0)//天数		
	,itemId(0)//物品编号		
	,itemName("")//物品名称		
	,itemType(0)//物品类型		
	,itemNumber(0)//物品数量		
	{};

	short id;
	short day;
	int itemId;
	string itemName;
	int itemType;
	int itemNumber;
};
#endif
