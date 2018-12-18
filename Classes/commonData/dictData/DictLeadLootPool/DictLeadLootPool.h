#ifndef __DictLeadLootPool__
#define __DictLeadLootPool__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictLeadLootPool:public Ref
{
public:
	DictLeadLootPool():	
	id(0)//ID		
	,itemId(0)//物品ID		
	,type(0)//物品类型		
	,number(0)//数量		
	,weight(0)//物品权重		
	,itemPool(0)//物品库类别		
	,randomType(0)//随机类别		
	{};

	int id;
	int itemId;
	int type;
	int number;
	int weight;
	int itemPool;
	short randomType;
};
#endif
