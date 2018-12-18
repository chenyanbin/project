#ifndef __DictLeadCost__
#define __DictLeadCost__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictLeadCost:public Ref
{
public:
	DictLeadCost():	
	id(0)//ID		
	,conId(0)//角色属性枚举ID		
	,conVal(0)//价值数量		
	,conValTen(0)//十连抽数量		
	,freeCoolDown(0)//免费cd时间		
	,freeTimesFirstDay(0)//首日免费次数		
	,freeTimesLimited(0)//累计免费次数上限		
	{};

	int id;
	int conId;
	int conVal;
	int conValTen;
	int freeCoolDown;
	short freeTimesFirstDay;
	short freeTimesLimited;
};
#endif
