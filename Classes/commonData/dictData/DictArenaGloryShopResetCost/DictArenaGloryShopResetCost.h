#ifndef __DictArenaGloryShopResetCost__
#define __DictArenaGloryShopResetCost__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictArenaGloryShopResetCost:public Ref
{
public:
	DictArenaGloryShopResetCost():	
	id(0)//编号		
	,resetTimes(0)//刷新次数		
	,gold(0)//花费元宝		
	{};

	int id;
	short resetTimes;
	int gold;
};
#endif
