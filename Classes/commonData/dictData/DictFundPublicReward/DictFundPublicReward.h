#ifndef __DictFundPublicReward__
#define __DictFundPublicReward__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictFundPublicReward:public Ref
{
public:
	DictFundPublicReward():	
	id(0)//ID		
	,buyNumber(0)//购买人数		
	,itemId(0)//物品编号		
	,itemName("")//物品名称		
	,itemType(0)//物品类型		
	,itemNumber(0)//物品数量		
	{};

	short id;
	short buyNumber;
	int itemId;
	string itemName;
	int itemType;
	int itemNumber;
};
#endif
