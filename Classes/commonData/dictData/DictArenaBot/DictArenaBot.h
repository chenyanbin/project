#ifndef __DictArenaBot__
#define __DictArenaBot__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictArenaBot:public Ref
{
public:
	DictArenaBot():	
	rank(0)//排名		
	,hero1Id(0)//队员1武将ID		
	,hero1Level(0)//队员1武将等级		
	,hero1Quality(0)//队员1武将品质		
	,hero1Prestige(0)//队员1武将星级		
	,hero2Id(0)//队员2武将ID		
	,hero2Level(0)//队员2武将等级		
	,hero2Quality(0)//队员2武将品质		
	,hero2Prestige(0)//队员2武将星级		
	,hero3Id(0)//队员3武将ID		
	,hero3Level(0)//队员3武将等级		
	,hero3Quality(0)//队员3武将品质		
	,hero3Prestige(0)//队员3武将星级		
	,playerName("")//队伍名称		
	,playerFightPower(0)//战力和		
	{};

	short rank;
	int hero1Id;
	short hero1Level;
	short hero1Quality;
	short hero1Prestige;
	int hero2Id;
	short hero2Level;
	short hero2Quality;
	short hero2Prestige;
	int hero3Id;
	short hero3Level;
	short hero3Quality;
	short hero3Prestige;
	string playerName;
	int playerFightPower;
};
#endif
