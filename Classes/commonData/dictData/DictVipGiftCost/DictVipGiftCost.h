#ifndef __DictVipGiftCost__
#define __DictVipGiftCost__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictVipGiftCost:public Ref
{
public:
	DictVipGiftCost():	
	id(0)//VIP等级		
	,day("")//物品名称		
	,itemId("")//物品描述		
	,cost(0)//原价		
	,costCheap(0)//特价		
	{};

	short id;
	string day;
	string itemId;
	int cost;
	int costCheap;
};
#endif
