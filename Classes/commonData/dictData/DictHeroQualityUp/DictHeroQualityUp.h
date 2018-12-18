#ifndef __DictHeroQualityUp__
#define __DictHeroQualityUp__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictHeroQualityUp:public Ref
{
public:
	DictHeroQualityUp():	
	quality(0)//品质等级		
	,qualityDesc("")//品质描述		
	,attack1Item1Id(0)//升品道具1（无属性）		
	,attack2Item1Id(0)//升品道具1（火焰）		
	,attack3Item1Id(0)//升品道具1（冰霜）		
	,attack4Item1Id(0)//升品道具1（雷电）		
	,attack5Item1Id(0)//升品道具1（无双）		
	,attack6Item1Id(0)//升品道具1（巫毒）		
	,item1Number(0)//道具1需求数量		
	,item2Id(0)//升品道具2		
	,item2Number(0)//道具2需求数量		
	,item3Id(0)//升品道具3		
	,item3Number(0)//道具3需求数量		
	,item4Id(0)//升品道具4		
	,item4Number(0)//道具4需求数量		
	{};

	short quality;
	string qualityDesc;
	int attack1Item1Id;
	int attack2Item1Id;
	int attack3Item1Id;
	int attack4Item1Id;
	int attack5Item1Id;
	int attack6Item1Id;
	short item1Number;
	int item2Id;
	short item2Number;
	int item3Id;
	short item3Number;
	int item4Id;
	short item4Number;
};
#endif
