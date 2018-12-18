#ifndef __DictEquipHardenLevel__
#define __DictEquipHardenLevel__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictEquipHardenLevel:public Ref
{
public:
	DictEquipHardenLevel():	
	id(0)//ID		
	,level(0)//玩家等级		
	,quality(0)//装备品质上限		
	,levelUp(0)//装备等级上限		
	{};

	int id;
	short level;
	int quality;
	short levelUp;
};
#endif
