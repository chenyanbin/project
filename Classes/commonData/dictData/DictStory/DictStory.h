#ifndef __DictStory__
#define __DictStory__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictStory:public Ref
{
public:
	DictStory():	
	id(0)//ID		
	,triggerType(0)//出现时机类型		
	,triggerId(0)//任务或关卡战斗ID		
	,triggerNode(0)//触发时机		
	,speakerType(0)//说话者类型		
	,speakerId(0)//说话者ID		
	,speakerPosition(0)//说话者位置		
	,speakerName("")//对话者名称		
	,text("")//对话内容		
	,order(0)//对话次序		
	{};

	int id;
	int triggerType;
	int triggerId;
	short triggerNode;
	int speakerType;
	int speakerId;
	short speakerPosition;
	string speakerName;
	string text;
	short order;
};
#endif
