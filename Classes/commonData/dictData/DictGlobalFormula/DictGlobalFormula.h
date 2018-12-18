#ifndef __DictGlobalFormula__
#define __DictGlobalFormula__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictGlobalFormula:public Ref
{
public:
	DictGlobalFormula():	
	id(0)//ID		
	,name("")//英文名		
	,type("")//中文名		
	,usage("")//用途		
	,valueType("")//值类型		
	,value("")//值		
	{};

	int id;
	string name;
	string type;
	string usage;
	string valueType;
	string value;
};
#endif
