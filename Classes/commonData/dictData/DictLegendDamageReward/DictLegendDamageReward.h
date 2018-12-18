#ifndef __DictLegendDamageReward__
#define __DictLegendDamageReward__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictLegendDamageReward:public Ref
{
public:
	DictLegendDamageReward():	
	id(0)//ID		
	,monsterLevel(0)//怪等级		
	,hurtCoin1(0)//1%伤害铜钱		
	,hurtCoin2(0)//2%伤害铜钱		
	,hurtCoin3(0)//3%伤害铜钱		
	,hurtCoin5(0)//5%伤害铜钱		
	,hurtCoin10(0)//10%伤害铜钱		
	,hurtCoin20(0)//20%伤害铜钱		
	,hurtCoin40(0)//40%伤害铜钱		
	,hurtCoin60(0)//60%伤害铜钱		
	,hurtCoin80(0)//80%伤害铜钱		
	,hurtCoin100(0)//100%伤害铜钱		
	{};

	int id;
	int monsterLevel;
	int hurtCoin1;
	int hurtCoin2;
	int hurtCoin3;
	int hurtCoin5;
	int hurtCoin10;
	int hurtCoin20;
	int hurtCoin40;
	int hurtCoin60;
	int hurtCoin80;
	int hurtCoin100;
};
#endif
