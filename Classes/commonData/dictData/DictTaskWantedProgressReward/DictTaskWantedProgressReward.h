#ifndef __DictTaskWantedProgressReward__
#define __DictTaskWantedProgressReward__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictTaskWantedProgressReward:public Ref
{
public:
	DictTaskWantedProgressReward():	
	id(0)//ID		
	,level(0)//玩家等级		
	,starNumberProgress(0)//进度		
	,conId(0)//角色属性枚举ID		
	,conVal(0)//价值数量		
	{};

	int id;
	int level;
	short starNumberProgress;
	int conId;
	int conVal;
};
#endif
