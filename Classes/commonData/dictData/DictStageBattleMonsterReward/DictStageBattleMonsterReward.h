#ifndef __DictStageBattleMonsterReward__
#define __DictStageBattleMonsterReward__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictStageBattleMonsterReward:public Ref
{
public:
	DictStageBattleMonsterReward():	
	stageMonsterId(0)//关卡怪ID		
	,monsterName("")//关卡怪名称		
	,itemId(0)//物品ID		
	,itemName("")//物品名称		
	,itemType(0)//物品类型		
	,minCount(0)//下限数量		
	,maxCount(0)//上限数量		
	,odds(0)//获得几率,每行单独计算，与random(10000)比较		
	,resource("")//资源名称		
	{};

	int stageMonsterId;
	string monsterName;
	int itemId;
	string itemName;
	int itemType;
	int minCount;
	int maxCount;
	int odds;
	string resource;
};
#endif
