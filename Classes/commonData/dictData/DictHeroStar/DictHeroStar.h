#ifndef __DictHeroStar__
#define __DictHeroStar__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictHeroStar:public Ref
{
public:
	DictHeroStar():	
	id(0)//ID		
	,level(0)//星级等级		
	,propUpMultiple(0)//星提升倍率		
	,lootUp(0)//星级副本加成		
	,toBook(0)//同名卡转化碎片		
	{};

	int id;
	short level;
	double propUpMultiple;
	short lootUp;
	short toBook;
};
#endif
