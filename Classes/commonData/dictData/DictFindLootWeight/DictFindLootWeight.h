#ifndef __DictFindLootWeight__
#define __DictFindLootWeight__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictFindLootWeight:public Ref
{
public:
	DictFindLootWeight():	
	quality1ItemId(0)//品质1物品ID		
	,quality2ItemId(0)//品质2物品ID		
	,quality3ItemId(0)//品质3物品ID		
	,quality4ItemId(0)//品质4物品ID		
	,quality5ItemId(0)//品质5物品ID		
	,quality6ItemId(0)//品质6物品ID		
	,quality7ItemId(0)//品质7物品ID		
	,quality8ItemId(0)//品质8物品ID		
	,type(0)//物品类型		
	,chooseWeightStart(0)//品类选择权重值		
	,chooseWeightRule(0)//品类选择区段值		
	{};

	int quality1ItemId;
	int quality2ItemId;
	int quality3ItemId;
	int quality4ItemId;
	int quality5ItemId;
	int quality6ItemId;
	int quality7ItemId;
	int quality8ItemId;
	int type;
	int chooseWeightStart;
	int chooseWeightRule;
};
#endif
