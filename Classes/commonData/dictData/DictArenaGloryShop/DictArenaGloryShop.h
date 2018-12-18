#ifndef __DictArenaGloryShop__
#define __DictArenaGloryShop__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictArenaGloryShop:public Ref
{
public:
	DictArenaGloryShop():	
	id(0)//ID		
	,itemId(0)//物品ID		
	,name("")//物品名称		
	,type(0)//物品类型		
	,sellNumber(0)//数量		
	,sellGold(0)//荣誉价格		
	,isChange(0)//固定标志		
	,quality(0)//物品品质		
	{};

	int id;
	int itemId;
	string name;
	int type;
	short sellNumber;
	int sellGold;
	short isChange;
	int quality;
};
#endif
