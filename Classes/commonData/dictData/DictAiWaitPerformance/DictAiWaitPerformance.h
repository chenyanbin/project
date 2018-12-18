#ifndef __DictAiWaitPerformance__
#define __DictAiWaitPerformance__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictAiWaitPerformance:public Ref
{
public:
	DictAiWaitPerformance():	
	ID(0)//编号		
	,desc("")//备注		
	,wonder(0)//反复走		
	,flank(0)//尝试绕后		
	,standBy(0)//站立等待		
	,standBack(0)//慢速远离		
	{};

	int ID;
	string desc;
	int wonder;
	int flank;
	int standBy;
	int standBack;
};
#endif
