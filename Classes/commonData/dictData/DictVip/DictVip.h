#ifndef __DictVip__
#define __DictVip__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictVip:public Ref
{
public:
	DictVip():	
	vipLevel(0)//vip等级		
	,totalChargeGold(0)//vip升级经验		
	,desc("")//特权描述		
	,coinChargeTimes(0)//祈福次数		
	,buyStaminaTimes(0)//体力购买次数		
	,sweepCommand(0)//扫荡令		
	,findCommand(0)//寻访令		
	,stageBattleSweepTenTimes(0)//扫荡10次功能		
	,blackshopNormalSlot(0)//黑市低价区功能		
	,blackshopPlusSlot(0)//黑市高价区功能		
	,arenaTimesbuy(0)//竞技场购买次数		
	,gemstoneTimesbuy(0)//宝石矿购买次数		
	{};

	short vipLevel;
	int totalChargeGold;
	string desc;
	short coinChargeTimes;
	short buyStaminaTimes;
	short sweepCommand;
	short findCommand;
	short stageBattleSweepTenTimes;
	short blackshopNormalSlot;
	short blackshopPlusSlot;
	short arenaTimesbuy;
	short gemstoneTimesbuy;
};
#endif
