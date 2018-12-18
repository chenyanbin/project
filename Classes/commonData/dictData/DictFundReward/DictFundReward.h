#ifndef __DictFundReward__
#define __DictFundReward__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictFundReward:public Ref
{
public:
	DictFundReward():	
	id(0)//ID		
	,level(0)//等级		
	,name("")//名称		
	,desc("")//描述		
	,gold(0)//获得元宝		
	{};

	short id;
	short level;
	string name;
	string desc;
	int gold;
};
#endif
