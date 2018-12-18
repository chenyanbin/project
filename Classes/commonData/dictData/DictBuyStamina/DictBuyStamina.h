#ifndef __DictBuyStamina__
#define __DictBuyStamina__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictBuyStamina:public Ref
{
public:
	DictBuyStamina():	
	id(0)//ID		
	,goldCost(0)//元宝花费		
	,stamina(0)//体力值		
	{};

	short id;
	int goldCost;
	short stamina;
};
#endif
