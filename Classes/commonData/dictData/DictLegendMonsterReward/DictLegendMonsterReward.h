#ifndef __DictLegendMonsterReward__
#define __DictLegendMonsterReward__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictLegendMonsterReward:public Ref
{
public:
	DictLegendMonsterReward():	
	id(0)//ID		
	,stageBattleId(0)//关卡ID		
	,normalOrPrestige(0)//普通或声望		
	,stageBattleName(0)//掉落品级		
	,itemType(0)//掉落物品类型		
	,itemId(0)//掉落物品ID		
	,heroPrestige(0)//武将声望		
	,itemNumber(0)//掉落数量		
	{};

	int id;
	int stageBattleId;
	short normalOrPrestige;
	short stageBattleName;
	int itemType;
	int itemId;
	short heroPrestige;
	short itemNumber;
};
#endif
