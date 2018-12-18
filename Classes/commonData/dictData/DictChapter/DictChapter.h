#ifndef __DictChapter__
#define __DictChapter__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictChapter:public Ref
{
public:
	DictChapter():	
	id(0)//章节ID		
	,name("")//章节名称		
	,indexOrder(0)//顺序		
	,resourceBg("")//背景素材		
	,resourceFront("")//前景		
	,resourceSky("")//天气		
	,bossId(0)//bossID		
	,levelOpen(0)//开启等级		
	{};

	int id;
	string name;
	short indexOrder;
	string resourceBg;
	string resourceFront;
	string resourceSky;
	int bossId;
	short levelOpen;
};
#endif
