#ifndef __DictItemBook__
#define __DictItemBook__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictItemBook:public Ref
{
public:
	DictItemBook():	
	id(0)//编号		
	,name("")//物品名称		
	,type(0)//物品类型		
	,quality(0)//物品品质		
	,stackNumber(0)//叠加数量		
	,seq(0)//背包顺序		
	,heroId(0)//对应英雄ID		
	,desc("")//描述		
	,resource("")//资源素材		
	{};

	int id;
	string name;
	int type;
	int quality;
	short stackNumber;
	short seq;
	int heroId;
	string desc;
	string resource;
};
#endif
