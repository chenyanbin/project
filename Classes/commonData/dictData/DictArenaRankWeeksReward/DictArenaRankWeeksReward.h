#ifndef __DictArenaRankWeeksReward__
#define __DictArenaRankWeeksReward__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictArenaRankWeeksReward:public Ref
{
public:
	DictArenaRankWeeksReward():	
	id(0)//ID		
	,rankMax(0)//名次上限		
	,rankMin(0)//名次下限		
	,glod(0)//获得元宝		
	,glory(0)//获得荣誉		
	{};

	int id;
	int rankMax;
	int rankMin;
	int glod;
	int glory;
};
#endif
