#ifndef __DictItem__
#define __DictItem__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictItem:public Ref
{
public:
	DictItem():	
	id(0)//编号		
	,name("")//物品名称		
	,type(0)//物品类型		
	,typeUse(0)//物品使用类型		
	,subType(0)//细化类型		
	,quality(0)//物品品质		
	,stackNumber(0)//叠加数量		
	,backPackSell(0)//是否背包出售		
	,sellingPrice(0)//出售价格		
	,backPackUse(0)//是否可在背包中使用		
	,seq(0)//背包顺序		
	,desc("")//描述		
	,resource("")//资源素材		
	{};

	int id;
	string name;
	int type;
	int typeUse;
	short subType;
	int quality;
	short stackNumber;
	short backPackSell;
	int sellingPrice;
	short backPackUse;
	short seq;
	string desc;
	string resource;
};
#endif
