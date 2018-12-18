#ifndef __DictCardCost__
#define __DictCardCost__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictCardCost:public Ref
{
public:
	DictCardCost():	
	id(0)//编号		
	,name("")//物品名称		
	,desc("")//描述		
	,price(0)//人民币价格		
	,goldThen(0)//立即获得元宝		
	,goldDaily(0)//每日可领元宝		
	{};

	short id;
	string name;
	string desc;
	int price;
	int goldThen;
	int goldDaily;
};
#endif
