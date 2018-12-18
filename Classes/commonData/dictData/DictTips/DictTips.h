#ifndef __DictTips__
#define __DictTips__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictTips:public Ref
{
public:
	DictTips():	
	id(0)//ID		
	,desc("")//描述		
	,chRgb("")//颜色值		
	{};

	int id;
	string desc;
	string chRgb;
};
#endif
