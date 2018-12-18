#ifndef __DictNewGuide__
#define __DictNewGuide__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictNewGuide:public Ref
{
public:
	DictNewGuide():	
	id(0)//ID		
	,function(0)//功能ID		
	,newGuideEvent(0)//新手事件ID		
	,resource(0)//引导员资源		
	,desc("")//引导员对话内容		
	,orderIndex(0)//次序		
	,place(0)//引导员位置		
	,arrow(0)//是否有箭头		
	,x(0)//箭头位置x		
	,y(0)//箭头位置y		
	,arrowDirect(0)//箭头方向		
	,bottom(0)//是否指向底部导航		
	,goFunction(0)//前往功能模块		
	,isToSever(0)//是否通知服务器		
	,bottomId(0)//按钮ID		
	,isPause(0)//引导暂停		
	,breakpoint(0)//断点续连		
	{};

	int id;
	int function;
	int newGuideEvent;
	int resource;
	string desc;
	short orderIndex;
	short place;
	short arrow;
	short x;
	short y;
	short arrowDirect;
	short bottom;
	short goFunction;
	short isToSever;
	short bottomId;
	short isPause;
	short breakpoint;
};
#endif
