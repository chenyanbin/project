#ifndef __DictItemHero__
#define __DictItemHero__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictItemHero:public Ref
{
public:
	DictItemHero():	
	id(0)//编号		
	,name("")//物品名称		
	,type(0)//物品类型		
	,quality(0)//物品品质		
	,star(0)//物品星级		
	,heroId(0)//对应英雄ID		
	,desc("")//描述		
	,resource("")//资源素材		
	,sellOrder(0)//出售顺序		
	{};

	int id;
	string name;
	int type;
	int quality;
	int star;
	int heroId;
	string desc;
	string resource;
	short sellOrder;
};
#endif
