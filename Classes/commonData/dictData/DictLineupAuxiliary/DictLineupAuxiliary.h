#ifndef __DictLineupAuxiliary__
#define __DictLineupAuxiliary__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictLineupAuxiliary:public Ref
{
public:
	DictLineupAuxiliary():	
	id(0)//阵容ID		
	,desc("")//助阵位名称		
	,openLevel(0)//开启等级		
	,attribute(0)//增加属性类别		
	,qualityDefault(0)//默认品级		
	,star1(0)//星级1		
	,star2(0)//星级2		
	,star3(0)//星级3		
	,star4(0)//星级4		
	,star5(0)//星级5		
	{};

	int id;
	string desc;
	int openLevel;
	short attribute;
	short qualityDefault;
	double star1;
	double star2;
	double star3;
	double star4;
	double star5;
};
#endif
