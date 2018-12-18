#ifndef __DictLuckyGoldTime__
#define __DictLuckyGoldTime__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictLuckyGoldTime:public Ref
{
public:
	DictLuckyGoldTime():	
	id(0)//ID		
	,timeRequired(0)//每日在线时长		
	{};

	short id;
	int timeRequired;
};
#endif
