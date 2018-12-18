#ifndef __DictStage__
#define __DictStage__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictStage:public Ref
{
public:
	DictStage():	
	id(0)//关卡ID		
	,name("")//关卡名称		
	,inChaperId(0)//所属章节ID		
	,indexOrder(0)//顺序		
	,axisX(0)//x		
	,axisY(0)//y		
	,showNumber("")//序号		
	{};

	int id;
	string name;
	int inChaperId;
	short indexOrder;
	int axisX;
	int axisY;
	string showNumber;
};
#endif
