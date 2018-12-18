#ifndef __DictMusouBattle__
#define __DictMusouBattle__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictMusouBattle:public Ref
{
public:
	DictMusouBattle():	
	id(0)//ID		
	,name("")//关卡战斗名称		
	,desc("")//描述		
	,inStageId(0)//关卡ID		
	,type(0)//关卡类型		
	,indexOrder(0)//顺序		
	,playerLevel(0)//等级限制-玩家等级		
	,costPower(0)//消耗体力		
	,cardResource("")//卡牌背景素材		
	,mapResource("")//资源素材		
	,bgResource("")//关卡战斗卡牌背景图		
	,nameResource("")//关卡名称美术字资源		
	,envirEffect("")//环境特效		
	,skyEffect("")//天空特效		
	,background("")//后景资源		
	,LayerType(0)//战斗背景层演变形式		
	,battleMusic("")//战斗音乐		
	,battleTime(0)//战斗时间		
	{};

	int id;
	string name;
	string desc;
	short inStageId;
	int type;
	short indexOrder;
	short playerLevel;
	short costPower;
	string cardResource;
	string mapResource;
	string bgResource;
	string nameResource;
	string envirEffect;
	string skyEffect;
	string background;
	int LayerType;
	string battleMusic;
	short battleTime;
};
#endif
