#ifndef __DictStageBattleMonster__
#define __DictStageBattleMonster__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictStageBattleMonster:public Ref
{
public:
	DictStageBattleMonster():	
	id(0)//ID		
	,monsterId(0)//怪物ID		
	,monsterName("")//怪物名称		
	,stageBattleId(0)//关卡战斗ID		
	,monsterLevel(0)//怪物等级		
	,monsterQuality(0)//怪物品质		
	,monsterLevelElite(0)//精英怪物等级		
	,monsterQualityElite(0)//精英怪物品质		
	,sight(0)//警戒范围		
	,range(0)//追击范围		
	,speed(0)//移动速度		
	,type(0)//怪物类别		
	,health(0)//生命		
	,attack(0)//攻击		
	,defend(0)//防御		
	,critic(0)//暴击率		
	,tenaci(0)//韧性率		
	,hit(0)//命中率		
	,block(0)//格挡率		
	,damageAdd(0)//伤害加成率		
	,fireResist(0)//火焰抗性率		
	,iceResist(0)//冰霜抗性率		
	,boltResist(0)//雷电抗性率		
	,windResist(0)//物理抗性率		
	,poisonResist(0)//巫毒抗性率		
	,healthE(0)//生命精		
	,attackE(0)//攻击精		
	,defendE(0)//防御精		
	,criticE(0)//暴击率精		
	,tenaciE(0)//韧性率精		
	,hitE(0)//命中率精		
	,blockE(0)//格挡率精		
	,damageAddE(0)//伤害加成率精		
	,fireResistE(0)//火焰抗性率精		
	,iceResistE(0)//冰霜抗性率精		
	,boltResistE(0)//雷电抗性率精		
	,windResistE(0)//物理抗性率精		
	,poisonResistE(0)//巫毒抗性率精		
	,aiID(0)//AI选择		
	{};

	int id;
	int monsterId;
	string monsterName;
	int stageBattleId;
	short monsterLevel;
	int monsterQuality;
	short monsterLevelElite;
	int monsterQualityElite;
	short sight;
	short range;
	short speed;
	short type;
	int health;
	int attack;
	int defend;
	int critic;
	int tenaci;
	int hit;
	int block;
	int damageAdd;
	int fireResist;
	int iceResist;
	int boltResist;
	int windResist;
	int poisonResist;
	int healthE;
	int attackE;
	int defendE;
	int criticE;
	int tenaciE;
	int hitE;
	int blockE;
	int damageAddE;
	int fireResistE;
	int iceResistE;
	int boltResistE;
	int windResistE;
	int poisonResistE;
	int aiID;
};
#endif
