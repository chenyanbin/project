#ifndef __DictStageBuilding__
#define __DictStageBuilding__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictStageBuilding:public Ref
{
public:
	DictStageBuilding():	
	id(0)//建筑ID		
	,name("")//建筑名称		
	,inChaperId(0)//所属章节ID		
	,axisX(0)//x		
	,axisY(0)//y		
	,axisZ(0)//z		
	,resource("")//素材		
	{};

	int id;
	string name;
	int inChaperId;
	int axisX;
	int axisY;
	int axisZ;
	string resource;
};
#endif
