#ifndef __DictMonster__
#define __DictMonster__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictMonster:public Ref
{
public:
	DictMonster():	
	id(0)//编号		
	,name("")//姓名		
	,type(0)//怪物类型ID		
	,attackType(0)//攻击类型ID		
	,heroProp("")//怪物属性ID		
	,skill1(0)//普通技能1		
	,skill2(0)//普通技能2		
	,skill3(0)//普通技能3		
	,skill4(0)//普通技能4		
	,skill5(0)//普通技能5		
	,skill6(0)//跳跃技能6		
	,skill7(0)//必杀技能7		
	,skill8(0)//必杀技能8		
	,skill9(0)//必杀技能9		
	,skill10(0)//连携技能10		
	,skillJumpTime(0)//技能跳击时间		
	,resource("")//资源素材		
	,resourceHighShifting(0)//资源高度偏移		
	,resourceShifting(0)//资源左右偏移		
	,dieVoice("")//死亡音效		
	,aiId(0)//AI选择		
	,delayTime(0)//动作间隔		
	,ssTime(0)//免疫时间		
	,halfbodyrResource("")//半身像资源		
	{};

	int id;
	string name;
	int type;
	int attackType;
	string heroProp;
	int skill1;
	int skill2;
	int skill3;
	int skill4;
	int skill5;
	int skill6;
	int skill7;
	int skill8;
	int skill9;
	int skill10;
	double skillJumpTime;
	string resource;
	short resourceHighShifting;
	short resourceShifting;
	string dieVoice;
	int aiId;
	int delayTime;
	int ssTime;
	string halfbodyrResource;
};
#endif
