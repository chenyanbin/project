#ifndef __DictEquipSoldReturn__
#define __DictEquipSoldReturn__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictEquipSoldReturn:public Ref
{
public:
	DictEquipSoldReturn():	
	qlevel(0)//品质等级		
	,moneyReturn(0)//铜钱返还系数		
	{};

	short qlevel;
	double moneyReturn;
};
#endif
