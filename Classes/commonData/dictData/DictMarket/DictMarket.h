#ifndef __DictMarket__
#define __DictMarket__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictMarket:public Ref
{
public:
	DictMarket():	
	id(0)//编号		
	,itemId(0)//物品ID		
	,name("")//物品名称		
	,type(0)//物品类型		
	,sellingPriceMin(0)//出售价格下限		
	,sellingPriceMax(0)//出售价格上限		
	{};

	int id;
	int itemId;
	string name;
	int type;
	int sellingPriceMin;
	int sellingPriceMax;
};
#endif
