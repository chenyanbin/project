#ifndef __DictWay__
#define __DictWay__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictWay:public Ref
{
public:
	DictWay():	
	id(0)//ID		
	,name("")//系统名		
	,desc("")//描述		
	,desc2("")//描述公式		
	,itemNumber(0)//条数		
	,quality(0)//品质上限		
	,useTye(0)//用处		
	,function(0)//功能模块		
	,resource("")//资源图标		
	{};

	short id;
	string name;
	string desc;
	string desc2;
	short itemNumber;
	short quality;
	short useTye;
	int function;
	string resource;
};
#endif
