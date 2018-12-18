#ifndef __DictLegendBattleMonster__
#define __DictLegendBattleMonster__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictLegendBattleMonster:public Ref
{
public:
	DictLegendBattleMonster():	
	id(0)//ID		
	,bossName("")//怪物名称		
	,team(0)//分组id		
	,monsterQuality(0)//怪物品质		
	,sight(0)//警戒范围		
	,range(0)//追击范围		
	,speed(0)//移动速度		
	,type(0)//怪物类别		
	,aiID(0)//AI选择		
	{};

	int id;
	string bossName;
	int team;
	int monsterQuality;
	short sight;
	short range;
	short speed;
	short type;
	int aiID;
};
#endif
