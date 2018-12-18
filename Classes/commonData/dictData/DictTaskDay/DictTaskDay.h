#ifndef __DictTaskDay__
#define __DictTaskDay__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictTaskDay:public Ref
{
public:
	DictTaskDay():	
	id(0)//任务ID		
	,name("")//任务名称		
	,category(0)//任务类型		
	,quality(0)//任务品质		
	,level(0)//可接任务玩家等级		
	,bonusExp(0)//经验铜钱倍数		
	,desc("")//描述		
	,progress(0)//完成进度		
	,taskType(0)//完成条件类型		
	,finishCon1("")//完成条件值1		
	,finishCon2("")//完成条件值2		
	,finishCon3("")//完成条件值3		
	{};

	int id;
	string name;
	int category;
	int quality;
	short level;
	short bonusExp;
	string desc;
	short progress;
	short taskType;
	string finishCon1;
	string finishCon2;
	string finishCon3;
};
#endif
