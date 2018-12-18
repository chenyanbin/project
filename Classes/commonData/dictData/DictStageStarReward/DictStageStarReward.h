#ifndef __DictStageStarReward__
#define __DictStageStarReward__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictStageStarReward:public Ref
{
public:
	DictStageStarReward():	
	id(0)//ID		
	,chapterId(0)//所属章节ID		
	,stageId(0)//所属关卡ID		
	,campaignType(0)//关卡类型		
	,starNumberProgress(0)//星数量领取进度		
	,conId(0)//角色属性枚举ID		
	,conVal(0)//普通本奖励数量		
	,conValElite(0)//精英本奖励数量		
	{};

	int id;
	int chapterId;
	int stageId;
	int campaignType;
	short starNumberProgress;
	int conId;
	int conVal;
	int conValElite;
};
#endif
