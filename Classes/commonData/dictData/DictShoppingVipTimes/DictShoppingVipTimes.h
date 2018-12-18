#ifndef __DictShoppingVipTimes__
#define __DictShoppingVipTimes__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictShoppingVipTimes:public Ref
{
public:
	DictShoppingVipTimes():	
	id(0)//售卖编号		
	,itemId(0)//物品ID		
	,itemName("")//物品名称		
	,vip0Buy(0)//VIP0购买		
	,vip1Buy(0)//VIP1购买		
	,vip2Buy(0)//VIP2购买		
	,vip3Buy(0)//VIP3购买		
	,vip4Buy(0)//VIP4购买		
	,vip5Buy(0)//VIP5购买		
	,vip6Buy(0)//VIP6购买		
	,vip7Buy(0)//VIP7购买		
	,vip8Buy(0)//VIP8购买		
	,vip9Buy(0)//VIP9购买		
	,vip10Buy(0)//VIP10购买		
	,vip11Buy(0)//VIP11购买		
	,vip12Buy(0)//VIP12购买		
	,vip13Buy(0)//VIP13购买		
	,vip14Buy(0)//VIP14购买		
	,vip15Buy(0)//VIP15购买		
	{};

	int id;
	int itemId;
	string itemName;
	int vip0Buy;
	int vip1Buy;
	int vip2Buy;
	int vip3Buy;
	int vip4Buy;
	int vip5Buy;
	int vip6Buy;
	int vip7Buy;
	int vip8Buy;
	int vip9Buy;
	int vip10Buy;
	int vip11Buy;
	int vip12Buy;
	int vip13Buy;
	int vip14Buy;
	int vip15Buy;
};
#endif
