#ifndef __DictStartHero__
#define __DictStartHero__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictStartHero:public Ref
{
public:
	DictStartHero():	
	id(0)//ID		
	,desc("")//描述		
	,itemHeroId(0)//获得武将道具ID		
	,heroNumber(0)//获得数量		
	{};

	int id;
	string desc;
	int itemHeroId;
	int heroNumber;
};
#endif
