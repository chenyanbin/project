#ifndef __DictStageBattleFKReward__
#define __DictStageBattleFKReward__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictStageBattleFKReward:public Ref
{
public:
	DictStageBattleFKReward():	
	id(0)//ID		
	,stageBattleId(0)//关卡ID		
	,stageBattleName("")//关卡名称		
	,itemType(0)//掉落物品类型		
	,itemId(0)//掉落物品ID		
	,itemNumber(0)//掉落数量		
	,itemTypeElite(0)//精英掉落物品类型		
	,itemIdElite(0)//精英掉落物品ID		
	,itemNumberElite(0)//精英掉落数量		
	{};

	int id;
	int stageBattleId;
	string stageBattleName;
	int itemType;
	int itemId;
	short itemNumber;
	int itemTypeElite;
	int itemIdElite;
	short itemNumberElite;
};
#endif
