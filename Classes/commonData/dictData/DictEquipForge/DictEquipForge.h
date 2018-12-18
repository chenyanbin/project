#ifndef __DictEquipForge__
#define __DictEquipForge__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictEquipForge:public Ref
{
public:
	DictEquipForge():	
	needEquit(0)//锻造原材料		
	,needItem(0)//所需道具ID1		
	,needItemNumber(0)//所需道具数量		
	,forgeEquip(0)//锻造出新装备		
	{};

	int needEquit;
	int needItem;
	short needItemNumber;
	int forgeEquip;
};
#endif
