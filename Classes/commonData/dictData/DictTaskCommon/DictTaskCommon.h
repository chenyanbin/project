#ifndef __DictTaskCommon__
#define __DictTaskCommon__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictTaskCommon:public Ref
{
public:
	DictTaskCommon():	
	id(0)//任务ID		
	,name("")//任务名称		
	,category(0)//分组		
	,quality(0)//任务品质		
	,level(0)//任务提交等级		
	,conditionTaskId(0)//前置任务ID		
	,seq(0)//任务次序		
	,desc("")//描述		
	,taskType(0)//任务类型		
	,finishCon1("")//完成条件值1		
	,finishCon2("")//完成条件值2		
	,finishCon3("")//完成条件值3		
	{};

	int id;
	string name;
	int category;
	int quality;
	short level;
	int conditionTaskId;
	short seq;
	string desc;
	short taskType;
	string finishCon1;
	string finishCon2;
	string finishCon3;
};
#endif
