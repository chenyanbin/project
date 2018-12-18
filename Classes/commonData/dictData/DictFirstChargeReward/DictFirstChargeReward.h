#ifndef __DictFirstChargeReward__
#define __DictFirstChargeReward__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictFirstChargeReward:public Ref
{
public:
	DictFirstChargeReward():	
	id(0)//物品ID		
	,name("")//物品名称		
	,type(0)//物品类型		
	,number(0)//数量		
	{};

	int id;
	string name;
	int type;
	int number;
};
#endif
