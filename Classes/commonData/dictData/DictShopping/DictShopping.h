#ifndef __DictShopping__
#define __DictShopping__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictShopping:public Ref
{
public:
	DictShopping():	
	id(0)//售卖编号		
	,itemId(0)//物品ID		
	,itemName("")//物品名称		
	,quality(0)//物品品质		
	,itemType(0)//物品类型		
	,gold(0)//元宝原价		
	,goldNow(0)//元宝现价		
	,desc("")//功能介绍		
	{};

	int id;
	int itemId;
	string itemName;
	int quality;
	int itemType;
	int gold;
	int goldNow;
	string desc;
};
#endif
