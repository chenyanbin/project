#ifndef __DictGemstoneMine__
#define __DictGemstoneMine__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictGemstoneMine:public Ref
{
public:
	DictGemstoneMine():	
	id(0)//ID		
	,times(0)//次数		
	,copper(0)//铜钱值		
	,gold(0)//元宝		
	{};

	short id;
	int times;
	int copper;
	int gold;
};
#endif
