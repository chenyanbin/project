#ifndef __DictHeroLevel__
#define __DictHeroLevel__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictHeroLevel:public Ref
{
public:
	DictHeroLevel():	
	heroLevel(0)//英雄等级		
	,heroLevelUpExp(0)//升级所需经验		
	{};

	short heroLevel;
	int heroLevelUpExp;
};
#endif
