#ifndef __DictMonsterPropLevel__
#define __DictMonsterPropLevel__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictMonsterPropLevel:public Ref
{
public:
	DictMonsterPropLevel():	
	id(0)//id		
	,monsterId(0)//monsterId		
	,level(0)//等级		
	,health(0)//生命		
	,attack(0)//攻击		
	,defend(0)//防御		
	,critic(0)//暴击		
	,tenaci(0)//韧性		
	,hit(0)//命中		
	,block(0)//格挡		
	,damageAdd(0)//伤害加成		
	,fireResist(0)//火焰抗性		
	,iceResist(0)//冰霜抗性		
	,boltResist(0)//雷电抗性		
	,windResist(0)//飓风抗性		
	,poisonResist(0)//巫毒抗性		
	{};

	int id;
	int monsterId;
	short level;
	int health;
	int attack;
	int defend;
	short critic;
	short tenaci;
	short hit;
	short block;
	short damageAdd;
	short fireResist;
	short iceResist;
	short boltResist;
	short windResist;
	short poisonResist;
};
#endif
