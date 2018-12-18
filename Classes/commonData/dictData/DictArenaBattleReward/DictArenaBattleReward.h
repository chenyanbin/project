#ifndef __DictArenaBattleReward__
#define __DictArenaBattleReward__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictArenaBattleReward:public Ref
{
public:
	DictArenaBattleReward():	
	id(0)//ID		
	,victoryGlory(0)//胜利获得荣誉		
	,loseGlory(0)//失败获得荣誉		
	{};

	short id;
	int victoryGlory;
	int loseGlory;
};
#endif
