#ifndef __DictHeroStarUpCost__
#define __DictHeroStarUpCost__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictHeroStarUpCost:public Ref
{
public:
	DictHeroStarUpCost():	
	id(0)//ID		
	,starLevel(0)//星级等级		
	,needBook(0)//升级该星级所需碎片数量		
	,combineNeedBook(0)//直接合成该星级所需碎片数量		
	,needCoin(0)//合成该星级所需花费铜钱		
	{};

	int id;
	short starLevel;
	short needBook;
	short combineNeedBook;
	int needCoin;
};
#endif
