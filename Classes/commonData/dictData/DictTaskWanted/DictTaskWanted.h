#ifndef __DictTaskWanted__
#define __DictTaskWanted__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictTaskWanted:public Ref
{
public:
	DictTaskWanted():	
	id(0)//任务ID		
	,name("")//任务名称		
	,type(0)//任务类型		
	,quality(0)//任务品质		
	,level(0)//任务接收等级		
	,conditionTaskId(0)//前置任务ID		
	,seq(0)//任务次序		
	,desc("")//描述		
	{};

	int id;
	string name;
	int type;
	int quality;
	short level;
	int conditionTaskId;
	short seq;
	string desc;
};
#endif
