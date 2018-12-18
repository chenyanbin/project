#ifndef __DictChargeCost__
#define __DictChargeCost__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictChargeCost:public Ref
{
public:
	DictChargeCost():	
	id(0)//编号		
	,name("")//物品名称		
	,desc("")//描述		
	,price(0)//人民币价格		
	,gold(0)//充值元宝数量		
	,goldFirst(0)//首次充值赠送元宝		
	,vipExpFirst(0)//首次充值赠送VIP经验		
	{};

	short id;
	string name;
	string desc;
	int price;
	int gold;
	int goldFirst;
	int vipExpFirst;
};
#endif
