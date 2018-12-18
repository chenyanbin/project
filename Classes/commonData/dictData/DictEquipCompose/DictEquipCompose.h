#ifndef __DictEquipCompose__
#define __DictEquipCompose__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictEquipCompose:public Ref
{
public:
	DictEquipCompose():	
	equipId(0)//合成装备ID		
	,materId(0)//所需材料ID		
	,materNumber(0)//需要数量		
	,resource("")//图片资源		
	{};

	int equipId;
	int materId;
	short materNumber;
	string resource;
};
#endif
