#ifndef __DictHeroQuality__
#define __DictHeroQuality__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictHeroQuality:public Ref
{
public:
	DictHeroQuality():	
	level(0)//品质等级		
	,nameDesp("")//品质描述		
	,name("")//品质名称显示		
	,ename("")//英文名称		
	,porpUpMultiple(0)//品质增长倍率		
	,levelUpLimit(0)//升品需求等级		
	,levelColour("")//品质对应边框颜色		
	,levelColourResource("")//品质对应边框素材		
	,baseCost(0)//基础领导力		
	,costLevelTenUp(0)//每10级提升领导力		
	,sellMultiple(0)//武将出售倍率		
	{};

	short level;
	string nameDesp;
	string name;
	string ename;
	double porpUpMultiple;
	short levelUpLimit;
	string levelColour;
	string levelColourResource;
	short baseCost;
	short costLevelTenUp;
	int sellMultiple;
};
#endif
