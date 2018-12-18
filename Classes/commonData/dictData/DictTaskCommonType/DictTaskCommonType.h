#ifndef __DictTaskCommonType__
#define __DictTaskCommonType__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictTaskCommonType:public Ref
{
public:
	DictTaskCommonType():	
	id(0)//ID		
	,name("")//类名		
	,tcName("")//检查类名		
	,progressFinishConN(0)//进度条件值		
	,function(0)//前往功能模块		
	,functionType(0)//前往类型		
	,requests("")//接口		
	{};

	short id;
	string name;
	string tcName;
	short progressFinishConN;
	int function;
	short functionType;
	string requests;
};
#endif
