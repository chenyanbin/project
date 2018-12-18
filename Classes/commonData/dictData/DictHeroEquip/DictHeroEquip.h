#ifndef __DictHeroEquip__
#define __DictHeroEquip__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictHeroEquip:public Ref
{
public:
	DictHeroEquip():	
	heroID(0)//英雄id		
	,heroName("")//英雄名称		
	,quality(0)//品质		
	,equipSlot1EquipID(0)//装备栏1对应装备id		
	,equipSlot2EquipID(0)//装备栏2对应装备id		
	,equipSlot3EquipID(0)//装备栏3对应装备id		
	,equipSlot4EquipID(0)//装备栏4对应装备id		
	,equipSlot5EquipID(0)//装备栏5对应装备id		
	,equipSlot6EquipID(0)//装备栏6对应装备id		
	{};

	int heroID;
	string heroName;
	short quality;
	int equipSlot1EquipID;
	int equipSlot2EquipID;
	int equipSlot3EquipID;
	int equipSlot4EquipID;
	int equipSlot5EquipID;
	int equipSlot6EquipID;
};
#endif
