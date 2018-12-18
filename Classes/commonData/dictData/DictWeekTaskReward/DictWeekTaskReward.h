#ifndef __DictWeekTaskReward__
#define __DictWeekTaskReward__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictWeekTaskReward:public Ref
{
public:
	DictWeekTaskReward():	
	id(0)//自动id		
	,weekTaskId(0)//七日任务id		
	,taskName("")//七日任务名称		
	,itemId(0)//物品编号		
	,itemName("")//物品名称		
	,itemType(0)//物品类型		
	,itemNumber(0)//物品数量		
	,days(0)//天数		
	{};

	int id;
	int weekTaskId;
	string taskName;
	int itemId;
	string itemName;
	int itemType;
	int itemNumber;
	int days;
};
#endif
