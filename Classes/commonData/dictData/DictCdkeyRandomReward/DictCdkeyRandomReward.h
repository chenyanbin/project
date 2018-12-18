#ifndef __DictCdkeyRandomReward__
#define __DictCdkeyRandomReward__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictCdkeyRandomReward:public Ref
{
public:
	DictCdkeyRandomReward():	
	id(0)//编号		
	,cdkey("")//礼包码		
	,cdkeyName("")//礼包名称		
	,itemId(0)//物品ID		
	,type(0)//物品类型		
	,number(0)//物品数量		
	{};

	int id;
	string cdkey;
	string cdkeyName;
	int itemId;
	int type;
	int number;
};
#endif
