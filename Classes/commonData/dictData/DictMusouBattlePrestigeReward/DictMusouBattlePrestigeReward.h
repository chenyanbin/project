#ifndef __DictMusouBattlePrestigeReward__
#define __DictMusouBattlePrestigeReward__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictMusouBattlePrestigeReward:public Ref
{
public:
	DictMusouBattlePrestigeReward():	
	id(0)//ID		
	,stageBattleId(0)//关卡ID		
	,stageBattleName("")//关卡名称		
	,itemType(0)//掉落物品类型		
	,itemId(0)//掉落物品ID		
	,itemNumber(0)//掉落数量		
	,lootOddsBase(0)//基础掉率		
	{};

	int id;
	int stageBattleId;
	string stageBattleName;
	int itemType;
	int itemId;
	short itemNumber;
	short lootOddsBase;
};
#endif
