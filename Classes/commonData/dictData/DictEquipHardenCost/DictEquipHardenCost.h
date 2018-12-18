#ifndef __DictEquipHardenCost__
#define __DictEquipHardenCost__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictEquipHardenCost:public Ref
{
public:
	DictEquipHardenCost():	
	id(0)//ID		
	,roleLevel(0)//角色等级上限		
	,equipHardenLevel(0)//装备强化等级		
	,quality1Cost(0)//品质1花费铜钱		
	,quality2Cost(0)//品质2花费铜钱		
	,quality3Cost(0)//品质3花费铜钱		
	,quality4Cost(0)//品质4花费铜钱		
	,quality5Cost(0)//品质5花费铜钱		
	,quality6Cost(0)//品质6花费铜钱		
	,quality7Cost(0)//品质7花费铜钱		
	,quality8Cost(0)//品质8花费铜钱		
	,quality9Cost(0)//品质9花费铜钱		
	,quality10Cost(0)//品质10花费铜钱		
	,quality11Cost(0)//品质11花费铜钱		
	,quality12Cost(0)//品质12花费铜钱		
	{};

	short id;
	short roleLevel;
	short equipHardenLevel;
	int quality1Cost;
	int quality2Cost;
	int quality3Cost;
	int quality4Cost;
	int quality5Cost;
	int quality6Cost;
	int quality7Cost;
	int quality8Cost;
	int quality9Cost;
	int quality10Cost;
	int quality11Cost;
	int quality12Cost;
};
#endif
