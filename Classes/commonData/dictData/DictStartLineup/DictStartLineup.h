#ifndef __DictStartLineup__
#define __DictStartLineup__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictStartLineup:public Ref
{
public:
	DictStartLineup():	
	id(0)//ID		
	,desc("")//描述		
	,lineupId(0)//开启阵容ID		
	{};

	int id;
	string desc;
	int lineupId;
};
#endif
