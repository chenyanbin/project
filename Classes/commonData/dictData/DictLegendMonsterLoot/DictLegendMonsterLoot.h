#ifndef __DictLegendMonsterLoot__
#define __DictLegendMonsterLoot__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictLegendMonsterLoot:public Ref
{
public:
	DictLegendMonsterLoot():	
	id(0)//ID		
	,monsterLv(0)//怪等级		
	,class1(0)//品级1掉率		
	,class2(0)//品级2掉率		
	,class3(0)//品级3掉率		
	,class4(0)//品级4掉率		
	,class5(0)//品级5掉率		
	,class6(0)//品级6掉率		
	,class7(0)//品级7掉率		
	,class8(0)//品级8掉率		
	,class9(0)//品级9掉率		
	{};

	short id;
	short monsterLv;
	int class1;
	int class2;
	int class3;
	int class4;
	int class5;
	int class6;
	int class7;
	int class8;
	int class9;
};
#endif
