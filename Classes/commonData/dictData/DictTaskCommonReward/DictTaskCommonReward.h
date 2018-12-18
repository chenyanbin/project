#ifndef __DictTaskCommonReward__
#define __DictTaskCommonReward__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictTaskCommonReward:public Ref
{
public:
	DictTaskCommonReward():	
	taskId(0)//任务ID		
	,taskName("")//任务名称		
	,item1Type(0)//掉落物品类型		
	,item1Id(0)//掉落物品ID		
	,item1Number(0)//掉落数量		
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
