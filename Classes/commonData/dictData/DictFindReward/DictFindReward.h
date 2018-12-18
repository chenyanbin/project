#ifndef __DictFindReward__
#define __DictFindReward__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictFindReward:public Ref
{
public:
	DictFindReward():	
	effectId(0)//搜寻效果ID		
	,quality1WeightStart(0)//品质1初始值		
	,quality2WeightStart(0)//品质2初始值		
	,quality3WeightStart(0)//品质3初始值		
	,quality4WeightStart(0)//品质4初始值		
	,quality5WeightStart(0)//品质5初始值		
	,quality6WeightStart(0)//品质6初始值		
	,quality7WeightStart(0)//品质7初始值		
	,quality8WeightStart(0)//品质8初始值		
	,quality1WeightGrow(0)//品质1成长值		
	,quality2WeightGrow(0)//品质2成长值		
	,quality3WeightGrow(0)//品质3成长值		
	,quality4WeightGrow(0)//品质4成长值		
	,quality5WeightGrow(0)//品质5成长值		
	,quality6WeightGrow(0)//品质6成长值		
	,quality7WeightGrow(0)//品质7成长值		
	,quality8WeightGrow(0)//品质8成长值		
	,itemHeroWeightStart(0)//英雄初始值		
	,itemEquipWeightStart(0)//装备初始值		
	,itemBookWeightStart(0)//书信初始值		
	,itemMaterWeightStart(0)//材料初始值		
	,itemHeroWeightGrow(0)//英雄成长值		
	,itemEquipWeightGrow(0)//装备成长值		
	,itemBookWeightGrow(0)//书信成长值		
	,itemMaterWeightGrow(0)//材料成长值		
	{};

	short effectId;
	int quality1WeightStart;
	int quality2WeightStart;
	int quality3WeightStart;
	int quality4WeightStart;
	int quality5WeightStart;
	int quality6WeightStart;
	int quality7WeightStart;
	int quality8WeightStart;
	int quality1WeightGrow;
	int quality2WeightGrow;
	int quality3WeightGrow;
	int quality4WeightGrow;
	int quality5WeightGrow;
	int quality6WeightGrow;
	int quality7WeightGrow;
	int quality8WeightGrow;
	int itemHeroWeightStart;
	int itemEquipWeightStart;
	int itemBookWeightStart;
	int itemMaterWeightStart;
	int itemHeroWeightGrow;
	int itemEquipWeightGrow;
	int itemBookWeightGrow;
	int itemMaterWeightGrow;
};
#endif
