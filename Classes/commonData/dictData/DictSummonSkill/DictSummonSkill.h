#ifndef __DictSummonSkill__
#define __DictSummonSkill__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictSummonSkill:public Ref
{
public:
	DictSummonSkill():	
	id(0)//技能ID		
	,heroName("")//技能作用武将名称		
	,summonId1(0)//召唤生物1ID		
	,summonId1Number(0)//召唤生物1数量		
	,summonId1Time(0)//召唤生物1存在时间		
	,summonId2(0)//召唤生物2ID		
	,summonId2Number(0)//召唤生物2数量		
	,summonId2Time(0)//召唤生物2存在时间		
	,summonId3(0)//召唤生物3ID		
	,summonId3Number(0)//召唤生物3数量		
	,summonId3Time(0)//召唤生物3存在时间		
	{};

	int id;
	string heroName;
	int summonId1;
	short summonId1Number;
	short summonId1Time;
	int summonId2;
	short summonId2Number;
	short summonId2Time;
	int summonId3;
	short summonId3Number;
	short summonId3Time;
};
#endif
