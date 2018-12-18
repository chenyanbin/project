#ifndef __DictCdkeyReward__
#define __DictCdkeyReward__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictCdkeyReward:public Ref
{
public:
	DictCdkeyReward():	
	id(0)//编号		
	,cdkey("")//礼包码		
	,cdkeyName("")//礼包名称		
	,itemId(0)//物品ID		
	,type(0)//物品类型		
	,number(0)//物品数量		
	,times(0)//个人使用次数		
	{};

	int id;
	string cdkey;
	string cdkeyName;
	int itemId;
	int type;
	int number;
	int times;
};
#endif
