#ifndef __DictTaskDayReward__
#define __DictTaskDayReward__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictTaskDayReward:public Ref
{
public:
	DictTaskDayReward():	
	taskId(0)//任务ID		
	,taskName("")//任务名称		
	,item1Type(0)//掉落物品1类型		
	,item1Id(0)//掉落物品1ID		
	,item1Number(0)//掉落物品1数量		
	,item2Type(0)//掉落物品2类型		
	,item2Id(0)//掉落物品2ID		
	,item2Number(0)//掉落物品2数量		
	{};

	int taskId;
	string taskName;
	int item1Type;
	int item1Id;
	int item1Number;
	int item2Type;
	int item2Id;
	int item2Number;
};
#endif
