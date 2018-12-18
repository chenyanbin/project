#ifndef __DictLegendBattle__
#define __DictLegendBattle__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictLegendBattle:public Ref
{
public:
	DictLegendBattle():	
	bossId(0)//BossID		
	,name("")//关卡战斗名称		
	,desc("")//描述		
	,mapResource("")//资源素材		
	,nameResource("")//关卡半身像资源		
	,envirEffect("")//环境特效		
	,skyEffect("")//天空特效		
	,background("")//后景资源		
	,LayerType(0)//背景层演变形式		
	,battleMusic("")//战斗音乐		
	,isPause(0)//是否暂停		
	,battleTime(0)//战斗时间		
	{};

	int bossId;
	string name;
	string desc;
	string mapResource;
	string nameResource;
	string envirEffect;
	string skyEffect;
	string background;
	int LayerType;
	string battleMusic;
	short isPause;
	short battleTime;
};
#endif
