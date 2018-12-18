#ifndef __DictVipGift__
#define __DictVipGift__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictVipGift:public Ref
{
public:
	DictVipGift():	
	id(0)//ID		
	,day(0)//VIP等级		
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
