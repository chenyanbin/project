#ifndef __DictGemstoneMineRate__
#define __DictGemstoneMineRate__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictGemstoneMineRate:public Ref
{
public:
	DictGemstoneMineRate():	
	id(0)//ID		
	,critMultiple1(0)//暴击倍数		
	,critInitialValue1(0)//暴击初始值		
	,critGrowthValue1(0)//爆率成长值		
	{};

	short id;
	short critMultiple1;
	int critInitialValue1;
	int critGrowthValue1;
};
#endif
