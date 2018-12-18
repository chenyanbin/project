#ifndef __DictLeadLootWeight__
#define __DictLeadLootWeight__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictLeadLootWeight:public Ref
{
public:
	DictLeadLootWeight():	
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
	,effectId1(0)//搜索效果ID1		
	,effectId2(0)//搜索效果ID2		
	,effectId3(0)//搜索效果ID3		
	,effectId4(0)//搜索效果ID4		
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
	short effectId1;
	short effectId2;
	short effectId3;
	short effectId4;
};
#endif
