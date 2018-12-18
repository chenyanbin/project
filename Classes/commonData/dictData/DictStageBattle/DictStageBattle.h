#ifndef __DictStageBattle__
#define __DictStageBattle__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictStageBattle:public Ref
{
public:
	DictStageBattle():	
	id(0)//ID		
	,name("")//关卡战斗名称		
	,desc("")//描述		
	,inChapterId(0)//章节ID		
	,inStageId(0)//关卡ID		
	,indexOrder(0)//顺序		
	,playerLevel(0)//等级限制-玩家等级		
	,oneDayTimes(0)//每日次数		
	,costPower(0)//消耗体力		
	,playerLevelElite(0)//精英等级限制-玩家等级		
	,oneDayTimesElite(0)//精英每日次数		
	,costPowerElite(0)//精英消耗体力		
	,cardResource("")//卡牌背景素材		
	,mapResource("")//资源素材		
	,bgResource("")//关卡战斗卡牌背景图		
	,nameResource("")//关卡名称美术字资源		
	,envirEffect("")//环境特效		
	,skyEffect("")//天空特效		
	,background("")//后景资源		
	,LayerType(0)//背景层演变形式		
	,battleMusic("")//战斗音乐		
	,functionopen("")//功能开启		
	,isPause(0)//是否暂停		
	,starDetermine1(0)//星级判定1		
	,starDetermine2(0)//星级判定2		
	,starDetermine3(0)//星级判定3		
	,battleTime(0)//战斗时间		
	,victoryTime(0)//时间胜利		
	,battleExperience(0)//上阵经验		
	,publicExperience(0)//公共经验		
	{};

	int id;
	string name;
	string desc;
	int inChapterId;
	int inStageId;
	short indexOrder;
	short playerLevel;
	short oneDayTimes;
	int costPower;
	short playerLevelElite;
	short oneDayTimesElite;
	int costPowerElite;
	string cardResource;
	string mapResource;
	string bgResource;
	string nameResource;
	string envirEffect;
	string skyEffect;
	string background;
	int LayerType;
	string battleMusic;
	string functionopen;
	short isPause;
	short starDetermine1;
	double starDetermine2;
	short starDetermine3;
	short battleTime;
	short victoryTime;
	short battleExperience;
	short publicExperience;
};
#endif
