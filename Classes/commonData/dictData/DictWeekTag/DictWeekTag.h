#ifndef __DictWeekTag__
#define __DictWeekTag__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictWeekTag:public Ref
{
public:
	DictWeekTag():	
	id(0)//ID		
	,tag1Id(0)//标签1ID		
	,name1("")//标签1名称		
	,tag2Id(0)//标签2ID		
	,name2("")//标签2名称		
	{};

	short id;
	int tag1Id;
	string name1;
	int tag2Id;
	string name2;
};
#endif
