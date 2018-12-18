#ifndef __DictArenaTimesReset__
#define __DictArenaTimesReset__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictArenaTimesReset:public Ref
{
public:
	DictArenaTimesReset():	
	id(0)//编号		
	,cdTimes(0)//CD时间		
	,gold(0)//重置花费		
	{};

	int id;
	short cdTimes;
	int gold;
};
#endif
