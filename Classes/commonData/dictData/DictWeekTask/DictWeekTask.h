#ifndef __DictWeekTask__
#define __DictWeekTask__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictWeekTask:public Ref
{
public:
	DictWeekTask():	
	id(0)//七日任务ID		
	,name("")//七日任务名称		
	,days(0)//天数		
	,desc("")//描述		
	,taskType(0)//任务类型		
	,finishCon1("")//完成条件值1		
	,finishCon2("")//完成条件值2		
	,finishCon3("")//完成条件值3		
	,tag(0)//页签		
	{};

	int id;
	string name;
	int days;
	string desc;
	short taskType;
	string finishCon1;
	string finishCon2;
	string finishCon3;
	int tag;
};
#endif
