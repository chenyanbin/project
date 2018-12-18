#ifndef __DictLegendTouchOdds__
#define __DictLegendTouchOdds__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictLegendTouchOdds:public Ref
{
public:
	DictLegendTouchOdds():	
	id(0)//ID		
	,playerLevel(0)//等级		
	,vip0Touch(0)//VIP0触发概率		
	,vip1Touch(0)//VIP1触发概率		
	,vip2Touch(0)//VIP2触发概率		
	,vip3Touch(0)//VIP3触发概率		
	,vip4Touch(0)//VIP4触发概率		
	,vip5Touch(0)//VIP5触发概率		
	,vip6Touch(0)//VIP6触发概率		
	,vip7Touch(0)//VIP7触发概率		
	,vip8Touch(0)//VIP8触发概率		
	,vip9Touch(0)//VIP9触发概率		
	,vip10Touch(0)//VIP10触发概率		
	,vip11Touch(0)//VIP11触发概率		
	,vip12Touch(0)//VIP12触发概率		
	,vip13Touch(0)//VIP13触发概率		
	,vip14Touch(0)//VIP14触发概率		
	,vip15Touch(0)//VIP15触发概率		
	{};

	short id;
	short playerLevel;
	int vip0Touch;
	int vip1Touch;
	int vip2Touch;
	int vip3Touch;
	int vip4Touch;
	int vip5Touch;
	int vip6Touch;
	int vip7Touch;
	int vip8Touch;
	int vip9Touch;
	int vip10Touch;
	int vip11Touch;
	int vip12Touch;
	int vip13Touch;
	int vip14Touch;
	int vip15Touch;
};
#endif
