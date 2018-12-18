#ifndef __DictChapterStarReward__
#define __DictChapterStarReward__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictChapterStarReward:public Ref
{
public:
	DictChapterStarReward():	
	id(0)//ID		
	,chapterId(0)//所属章节		
	,campaignType(0)//关卡类型		
	,starNumberProgress(0)//星数量领取进度		
	,conId(0)//角色属性枚举ID		
	,conVal(0)//奖励数量		
	{};

	int id;
	int chapterId;
	int campaignType;
	short starNumberProgress;
	int conId;
	int conVal;
};
#endif
