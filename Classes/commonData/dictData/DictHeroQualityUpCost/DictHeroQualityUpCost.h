#ifndef __DictHeroQualityUpCost__
#define __DictHeroQualityUpCost__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictHeroQualityUpCost:public Ref
{
public:
	DictHeroQualityUpCost():	
	quality(0)//品质等级		
	,qualityDesc("")//品质名称		
	,coin(0)//觉醒花费铜钱		
	{};

	short quality;
	string qualityDesc;
	int coin;
};
#endif
