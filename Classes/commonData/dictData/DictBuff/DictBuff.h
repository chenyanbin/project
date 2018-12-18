#ifndef __DictBuff__
#define __DictBuff__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictBuff:public Ref
{
public:
	DictBuff():	
	id(0)//ID		
	,desc("")//描述		
	,type(0)//BUFF类型ID		
	,attackType(0)//攻击类型ID		
	,target(0)//BUFF目标类型		
	,time(0)//BUFF持续时间		
	,onTime(0)//BUFF间隔时间		
	,hurt(0)//BUFF伤害系数		
	,effect(0)//BUFF效果系数		
	,resource("")//特效资源素材		
	,iconResource("")//图标资源素材		
	,x(0)//x轴偏移		
	,y(0)//y轴偏移		
	,point(0)//显示部位		
	,level(0)//显示层级		
	,voice("")//音效		
	,effectZoom(0)//特效资源缩放		
	,heroZoom(0)//目标武将缩放		
	,loopControl(0)//特效是否循环		
	,characterShow("")//飘字		
	{};

	int id;
	string desc;
	int type;
	int attackType;
	int target;
	short time;
	short onTime;
	short hurt;
	int effect;
	string resource;
	string iconResource;
	short x;
	short y;
	int point;
	short level;
	string voice;
	int effectZoom;
	int heroZoom;
	short loopControl;
	string characterShow;
};
#endif
