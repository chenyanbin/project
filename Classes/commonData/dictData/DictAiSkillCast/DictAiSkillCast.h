#ifndef __DictAiSkillCast__
#define __DictAiSkillCast__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictAiSkillCast:public Ref
{
public:
	DictAiSkillCast():	
	id(0)//ID		
	,desc("")//备注		
	,waitTimeId(0)//等待时长ID		
	,WaitPerformance(0)//等待行为ID		
	,s1Rate(0)//技能1施放权重		
	,s1Range(0)//技能1索敌范围		
	,s6Rate(0)//技能6施放权重		
	,s6Range(0)//技能6索敌范围		
	,s7Rate(0)//技能7施放权重		
	,s7Range(0)//技能7索敌范围		
	,s8Rate(0)//技能8施放权重		
	,s8Range(0)//技能8索敌范围		
	,s9Rate(0)//技能9施放权重		
	,s9Range(0)//技能9索敌范围		
	,s10Rate(0)//技能10施放权重		
	,s10Range(0)//技能10索敌范围		
	,s11Rate(0)//技能11施放权重		
	,s11Range(0)//技能11索敌范围		
	,firstSkill(0)//开幕技能		
	,fWaitTime(0)//开幕技能等待时间		
	{};

	int id;
	string desc;
	int waitTimeId;
	int WaitPerformance;
	int s1Rate;
	int s1Range;
	int s6Rate;
	int s6Range;
	int s7Rate;
	int s7Range;
	int s8Rate;
	int s8Range;
	int s9Rate;
	int s9Range;
	int s10Rate;
	int s10Range;
	int s11Rate;
	int s11Range;
	int firstSkill;
	int fWaitTime;
};
#endif
