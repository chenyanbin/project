#ifndef __DictBlackshop__
#define __DictBlackshop__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictBlackshop:public Ref
{
public:
	DictBlackshop():	
	id(0)//ID		
	,itemId(0)//物品ID		
	,name("")//物品名称		
	,type(0)//物品类型		
	,sellLocal(0)//低价区/高价区		
	,conId(0)//角色属性枚举ID		
	,conVal(0)//价格		
	,number(0)//数量		
	,weight(0)//权重		
	{};

	int id;
	int itemId;
	string name;
	int type;
	short sellLocal;
	int conId;
	int conVal;
	int number;
	int weight;
};
#endif
