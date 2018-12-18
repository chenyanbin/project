#ifndef __DictHeroLineupKarma__
#define __DictHeroLineupKarma__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictHeroLineupKarma:public Ref
{
public:
	DictHeroLineupKarma():	
	id(0)//缘分ID		
	,name("")//缘分名称		
	,desc("")//缘分描述（阵容）		
	,desc2("")//缘分长描述（武将技能）		
	,ownHero("")//缘分拥有武将		
	,ownHeroId(0)//缘分拥有武将ID		
	,karmaHero("")//缘分对应武将		
	,karmaHeroId(0)//缘分对应武将ID		
	,fightProp(0)//加成战斗属性项		
	,fightPropValue(0)//加成战斗属性值		
	{};

	int id;
	string name;
	string desc;
	string desc2;
	string ownHero;
	int ownHeroId;
	string karmaHero;
	int karmaHeroId;
	int fightProp;
	int fightPropValue;
};
#endif
