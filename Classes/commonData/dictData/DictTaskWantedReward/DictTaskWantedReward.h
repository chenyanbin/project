#ifndef __DictTaskWantedReward__
#define __DictTaskWantedReward__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictTaskWantedReward:public Ref
{
public:
	DictTaskWantedReward():	
	id(0)//ID		
	,taskId(0)//任务ID		
	,taskName("")//任务名称		
	,itemId(0)//掉落物品ID		
	{};

	int id;
	int taskId;
	string taskName;
	int itemId;
};
#endif
