#ifndef __DictTaskDayTypeMsg__
#define __DictTaskDayTypeMsg__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictTaskDayTypeMsg:public Ref
{
public:
	DictTaskDayTypeMsg():	
	id(0)//ID		
	,msgName("")//检查消息类名		
	,taskTypeId(0)//任务类型id		
	,taskTypeName("")//任务类型名称		
	{};

	short id;
	string msgName;
	short taskTypeId;
	string taskTypeName;
};
#endif
