#ifndef __DictItemQuality__
#define __DictItemQuality__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictItemQuality:public Ref
{
public:
	DictItemQuality():	
	id(0)//ID		
	,name("")//类名		
	,ename("")//英文名称		
	,levelUpLimit(0)//装备等级上限		
	,levelColour("")//品质对应边框颜色		
	,levelColourResource("")//品质对应边框素材		
	{};

	short id;
	string name;
	string ename;
	short levelUpLimit;
	string levelColour;
	string levelColourResource;
};
#endif
