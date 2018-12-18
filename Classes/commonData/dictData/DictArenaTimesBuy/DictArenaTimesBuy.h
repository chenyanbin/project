#ifndef __DictArenaTimesBuy__
#define __DictArenaTimesBuy__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictArenaTimesBuy:public Ref
{
public:
	DictArenaTimesBuy():	
	buyTimes(0)//购买次数		
	,gold(0)//购买消耗		
	{};

	short buyTimes;
	short gold;
};
#endif
