#ifndef __DictEquipHardenFightProp__
#define __DictEquipHardenFightProp__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictEquipHardenFightProp:public Ref
{
public:
	DictEquipHardenFightProp():	
	id(0)//装备编号		
	,name("")//物品名称		
	,quality(0)//装备品质		
	,limitLevel(0)//强化等级上限		
	,health(0)//生命		
	,healthLevelUp(0)//成长值		
	,attack(0)//攻击		
	,attackLevelUp(0)//成长值		
	,defend(0)//防御		
	,defendLevelUp(0)//成长值		
	,critic(0)//暴击率		
	,criticLevelUp(0)//成长值		
	,tenaci(0)//韧性率		
	,tenaciLevelUp(0)//成长值		
	,hit(0)//命中率		
	,hitLevelUp(0)//成长值		
	,block(0)//格挡率		
	,blockLevelUp(0)//成长值		
	{};

	int id;
	string name;
	short quality;
	short limitLevel;
	int health;
	int healthLevelUp;
	int attack;
	int attackLevelUp;
	int defend;
	int defendLevelUp;
	int critic;
	int criticLevelUp;
	int tenaci;
	int tenaciLevelUp;
	int hit;
	int hitLevelUp;
	int block;
	int blockLevelUp;
};
#endif
