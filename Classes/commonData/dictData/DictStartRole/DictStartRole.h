#ifndef __DictStartRole__
#define __DictStartRole__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictStartRole:public Ref
{
public:
	DictStartRole():	
	id(0)//ID,DictRolePropEnum.id		
	,name("")//类名		
	,ename("")//英文名称		
	,startValue(0)//初始数量		
	{};

	short id;
	string name;
	string ename;
	int startValue;
};
#endif
