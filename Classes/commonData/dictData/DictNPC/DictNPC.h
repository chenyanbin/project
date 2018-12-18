#ifndef __DictNPC__
#define __DictNPC__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictNPC:public Ref
{
public:
	DictNPC():	
	id(0)//ID		
	,name("")//姓名		
	,type(0)//NPC类型ID		
	,resource("")//资源素材		
	,resourceHighShifting(0)//资源高度偏移		
	,openFunction(0)//点击开启功能UI		
	,resourceShifting(0)//资源左右偏移		
	{};

	int id;
	string name;
	int type;
	string resource;
	short resourceHighShifting;
	int openFunction;
	short resourceShifting;
};
#endif
