#ifndef __DictBookCost__
#define __DictBookCost__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictBookCost:public Ref
{
public:
	DictBookCost():	
	id(0)//送礼次数		
	,conId(0)//角色属性枚举ID		
	,conVal(0)//价值数量		
	{};

	short id;
	int conId;
	int conVal;
};
#endif
