#ifndef __DictMusou__
#define __DictMusou__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictMusou:public Ref
{
public:
	DictMusou():	
	id(0)//关卡ID		
	,name("")//关卡名称		
	,inTypeEnumId(0)//所属关卡类型ID		
	,weekId1(0)//星期ID1		
	,openTime1("")//开启时间1		
	,closeTime1("")//关闭时间1		
	,weekId2(0)//星期ID2		
	,openTime2("")//开启时间2		
	,closeTime2("")//关闭时间2		
	,weekId3(0)//星期ID3		
	,openTime3("")//开启时间3		
	,closeTime3("")//关闭时间3		
	,weekId4(0)//星期ID4		
	,openTime4("")//开启时间4		
	,closeTime4("")//关闭时间4		
	,resource("")//资源		
	{};

	short id;
	string name;
	int inTypeEnumId;
	int weekId1;
	string openTime1;
	string closeTime1;
	int weekId2;
	string openTime2;
	string closeTime2;
	int weekId3;
	string openTime3;
	string closeTime3;
	int weekId4;
	string openTime4;
	string closeTime4;
	string resource;
};
#endif
