#ifndef __DictItemUseReward__
#define __DictItemUseReward__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictItemUseReward:public Ref
{
public:
	DictItemUseReward():	
	id(0)//ID		
	,stageBattleName("")//道具名称		
	,itemType1(0)//掉落物品类型1		
	,itemId1(0)//掉落物品ID1		
	,itemNumber1(0)//掉落数量1		
	,lootOddsBase1(0)//基础掉率1		
	,itemType2(0)//掉落物品类型2		
	,itemId2(0)//掉落物品ID2		
	,itemNumber2(0)//掉落数量2		
	,lootOddsBase2(0)//基础掉率2		
	,itemType3(0)//掉落物品类型3		
	,itemId3(0)//掉落物品ID3		
	,itemNumber3(0)//掉落数量3		
	,lootOddsBase3(0)//基础掉率3		
	{};

	int id;
	string stageBattleName;
	int itemType1;
	int itemId1;
	short itemNumber1;
	short lootOddsBase1;
	int itemType2;
	int itemId2;
	short itemNumber2;
	short lootOddsBase2;
	int itemType3;
	int itemId3;
	short itemNumber3;
	short lootOddsBase3;
};
#endif
