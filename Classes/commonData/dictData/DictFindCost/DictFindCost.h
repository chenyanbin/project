#ifndef __DictFindCost__
#define __DictFindCost__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictFindCost:public Ref
{
public:
	DictFindCost():	
	id(0)//ID		
	,conVal(0)//铜钱数量		
	,findTime(0)//搜寻时间		
	,findFastCostGold(0)//加速寻访花费元宝		
	{};

	int id;
	int conVal;
	int findTime;
	int findFastCostGold;
};
#endif
