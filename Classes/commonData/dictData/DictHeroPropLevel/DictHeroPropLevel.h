#ifndef __DictHeroPropLevel__
#define __DictHeroPropLevel__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictHeroPropLevel:public Ref
{
public:
	DictHeroPropLevel():	
	id(0)//id		
	,heroId(0)//heroId		
	,level(0)//等级		
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
	{};

	int id;
	int heroId;
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
