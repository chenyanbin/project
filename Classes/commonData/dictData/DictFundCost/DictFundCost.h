#ifndef __DictFundCost__
#define __DictFundCost__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictFundCost:public Ref
{
public:
	DictFundCost():	
	id(0)//编号		
	,name("")//物品名称		
	,desc("")//描述		
	,vipLimit(0)//VIP等级限制		
	,gold(0)//元宝花费		
	{};

	short id;
	string name;
	string desc;
	short vipLimit;
	short gold;
};
#endif
