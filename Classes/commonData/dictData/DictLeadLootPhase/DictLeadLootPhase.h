#ifndef __DictLeadLootPhase__
#define __DictLeadLootPhase__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictLeadLootPhase:public Ref
{
public:
	DictLeadLootPhase():	
	id(0)//ID		
	,conLimit(0)//消耗下限		
	,conMax(0)//消耗上限		
	,drawType(0)//抽卡类别		
	,resType(0)//资源类别		
	,conPhase(0)//消费阶段		
	{};

	int id;
	int conLimit;
	int conMax;
	short drawType;
	short resType;
	short conPhase;
};
#endif
