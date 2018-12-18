#ifndef __DictItemMater__
#define __DictItemMater__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictItemMater:public Ref
{
public:
	DictItemMater():	
	id(0)//编号		
	,name("")//物品名称		
	,type(0)//物品类型		
	,quality(0)//物品品质		
	,stackNumber(0)//叠加数量		
	,seq(0)//背包顺序		
	,desc("")//描述		
	,resource("")//资源素材		
	,targetId(0)//目标装备		
	,levelColour("")//品质对应边框颜色		
	{};

	int id;
	string name;
	int type;
	int quality;
	short stackNumber;
	short seq;
	string desc;
	string resource;
	int targetId;
	string levelColour;
};
#endif
