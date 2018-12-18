#ifndef __DictItemEquip__
#define __DictItemEquip__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictItemEquip:public Ref
{
public:
	DictItemEquip():	
	id(0)//编号		
	,name("")//物品名称		
	,type(0)//物品类型		
	,quality(0)//物品品质		
	,backPackSell(0)//是否背包出售		
	,sellingPrice(0)//出售价格		
	,backPackOrder(0)//背包顺序		
	,desc("")//描述		
	,resource("")//资源素材		
	,parts(0)//装备部位		
	,sellOrder(0)//出售顺序		
	,dropStageBattle(0)//掉落关卡		
	,levelColour("")//品质对应边框颜色		
	{};

	int id;
	string name;
	int type;
	int quality;
	short backPackSell;
	int sellingPrice;
	short backPackOrder;
	string desc;
	string resource;
	int parts;
	short sellOrder;
	int dropStageBattle;
	string levelColour;
};
#endif
