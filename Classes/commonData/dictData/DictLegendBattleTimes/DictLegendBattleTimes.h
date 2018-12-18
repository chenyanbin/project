#ifndef __DictLegendBattleTimes__
#define __DictLegendBattleTimes__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictLegendBattleTimes:public Ref
{
public:
	DictLegendBattleTimes():	
	id(0)//ID		
	,playerLevel(0)//等级		
	,vip0Times(0)//VIP0次数		
	,vip1Times(0)//VIP1次数		
	,vip2Times(0)//VIP2次数		
	,vip3Times(0)//VIP3次数		
	,vip4Times(0)//VIP4次数		
	,vip5Times(0)//VIP5次数		
	,vip6Times(0)//VIP6次数		
	,vip7Times(0)//VIP7次数		
	,vip8Times(0)//VIP8次数		
	,vip9Times(0)//VIP9次数		
	,vip10Times(0)//VIP10次数		
	,vip11Times(0)//VIP11次数		
	,vip12Times(0)//VIP12次数		
	,vip13Times(0)//VIP13次数		
	,vip14Times(0)//VIP14次数		
	,vip15Times(0)//VIP15次数		
	{};

	int id;
	int playerLevel;
	short vip0Times;
	short vip1Times;
	short vip2Times;
	short vip3Times;
	short vip4Times;
	short vip5Times;
	short vip6Times;
	short vip7Times;
	short vip8Times;
	short vip9Times;
	short vip10Times;
	short vip11Times;
	short vip12Times;
	short vip13Times;
	short vip14Times;
	short vip15Times;
};
#endif
