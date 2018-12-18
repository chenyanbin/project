#ifndef __DictLegend__
#define __DictLegend__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictLegend:public Ref
{
public:
	DictLegend():	
	id(0)//ID		
	,periods("")//期数，从1开始连续		
	,legendName("")//名将传名称		
	,openDate("")//开启日期		
	,openTime("")//开启时间		
	,closeDate("")//关闭日期		
	,closeTime("")//关闭时间		
	,multiItemHeroId(0)//倍卡武将ID		
	,rankItemHeroId(0)//排名奖励武将ID		
	{};

	int id;
	string periods;
	string legendName;
	string openDate;
	string openTime;
	string closeDate;
	string closeTime;
	int multiItemHeroId;
	int rankItemHeroId;
};
#endif
