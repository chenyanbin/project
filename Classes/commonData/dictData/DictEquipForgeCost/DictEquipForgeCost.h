#ifndef __DictEquipForgeCost__
#define __DictEquipForgeCost__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictEquipForgeCost:public Ref
{
public:
	DictEquipForgeCost():	
	quality(0)//被吞噬者品质		
	,consumeCoin(0)//花费铜钱		
	{};

	int quality;
	int consumeCoin;
};
#endif
