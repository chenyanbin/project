#ifndef __DictStageBattlePrestigeReward__
#define __DictStageBattlePrestigeReward__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictStageBattlePrestigeReward:public Ref
{
public:
	DictStageBattlePrestigeReward():	
	id(0)//ID		
	,stageBattleId(0)//关卡ID		
	,stageBattleName("")//关卡名称		
	,itemType(0)//掉落物品类型		
	,itemId(0)//掉落物品ID		
	,itemNumber(0)//掉落数量		
	,lootOddsBase(0)//基础掉率		
	,itemTypeElite(0)//精英掉落物品类型		
	,itemIdElite(0)//精英掉落物品ID		
	,itemNumberElite(0)//精英掉落数量		
	,lootOddsBaseElite(0)//精英基础掉率		
	{};

	int id;
	int stageBattleId;
	string stageBattleName;
	int itemType;
	int itemId;
	short itemNumber;
	short lootOddsBase;
	int itemTypeElite;
	int itemIdElite;
	short itemNumberElite;
	short lootOddsBaseElite;
};
#endif
