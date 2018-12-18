#ifndef __DictFindOpenCost__
#define __DictFindOpenCost__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictFindOpenCost:public Ref
{
public:
	DictFindOpenCost():	
	id(0)//阵容ID		
	,desc("")//阵容名称		
	,seq(0)//序列		
	,conId(0)//角色属性枚举ID		
	,conVal(0)//价值数量		
	{};

	int id;
	string desc;
	short seq;
	int conId;
	int conVal;
};
#endif
