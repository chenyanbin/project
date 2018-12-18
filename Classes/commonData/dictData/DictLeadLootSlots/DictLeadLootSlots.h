#ifndef __DictLeadLootSlots__
#define __DictLeadLootSlots__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictLeadLootSlots:public Ref
{
public:
	DictLeadLootSlots():	
	id(0)//ID		
	,drawType(0)//抽卡类别		
	,slot("")//空位抽取串		
	,consumeLv(0)//消费阶段		
	{};

	int id;
	int drawType;
	string slot;
	short consumeLv;
};
#endif
