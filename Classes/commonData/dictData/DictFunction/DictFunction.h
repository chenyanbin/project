#ifndef __DictFunction__
#define __DictFunction__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictFunction:public Ref
{
public:
	DictFunction():	
	id(0)//ID		
	,name("")//功能名称		
	,ename("")//英文名称		
	,roleLevel(0)//功能开启等级		
	,battleId(0)//功能开启关卡		
	,openingtext("")//功能开启说明		
	,resource("")//资源素材		
	{};

	short id;
	string name;
	string ename;
	int roleLevel;
	int battleId;
	string openingtext;
	string resource;
};
#endif
