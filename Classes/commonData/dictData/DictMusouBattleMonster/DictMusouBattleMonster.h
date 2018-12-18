#ifndef __DictMusouBattleMonster__
#define __DictMusouBattleMonster__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictMusouBattleMonster:public Ref
{
public:
	DictMusouBattleMonster():	
	id(0)//ID		
	,monsterId(0)//怪物ID		
	,monsterName("")//怪物名称		
	,stageBattleId(0)//关卡战斗ID		
	,monsterLevel(0)//怪物等级		
	,monsterQuality(0)//怪物品质		
	,sight(0)//警戒范围		
	,range(0)//追击范围		
	,speed(0)//移动速度		
	,type(0)//怪物类别		
	,amplificationFactor(0)//放大倍数		
	,aiID(0)//AI选择		
	{};

	int id;
	int monsterId;
	string monsterName;
	int stageBattleId;
	short monsterLevel;
	int monsterQuality;
	short sight;
	short range;
	short speed;
	short type;
	short amplificationFactor;
	int aiID;
};
#endif
