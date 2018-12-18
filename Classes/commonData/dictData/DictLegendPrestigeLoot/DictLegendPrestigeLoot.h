#ifndef __DictLegendPrestigeLoot__
#define __DictLegendPrestigeLoot__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictLegendPrestigeLoot:public Ref
{
public:
	DictLegendPrestigeLoot():	
	id(0)//ID		
	,prestige(0)//声望		
	,class1(0)//品级1掉率		
	,class2(0)//品级2掉率		
	,class3(0)//品级3掉率		
	,class4(0)//品级4掉率		
	,class5(0)//品级5掉率		
	,class6(0)//品级6掉率		
	{};

	short id;
	short prestige;
	int class1;
	int class2;
	int class3;
	int class4;
	int class5;
	int class6;
};
#endif
