#ifndef __DictResource__
#define __DictResource__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictResource:public Ref
{
public:
	DictResource():	
	id(0)//编号		
	,name("")//物品名称		
	,type(0)//物品类型		
	,quality(0)//物品品质		
	,propType(0)//资源类型		
	,number(0)//资源数量		
	,resource("")//资源素材		
	,desc("")//描述		
	{};

	int id;
	string name;
	int type;
	int quality;
	int propType;
	int number;
	string resource;
	string desc;
};
#endif
