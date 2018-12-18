#ifndef __DictBookUpper__
#define __DictBookUpper__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictBookUpper:public Ref
{
public:
	DictBookUpper():	
	id(0)//编号		
	,quality(0)//物品品质		
	,friendUpper(0)//友好度上限		
	{};

	short id;
	int quality;
	short friendUpper;
};
#endif
