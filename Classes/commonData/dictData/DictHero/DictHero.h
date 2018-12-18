#ifndef __DictHero__
#define __DictHero__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictHero:public Ref
{
public:
	DictHero():	
	id(0)//编号		
	,name("")//姓名		
	,sex(0)//性别		
	,force(0)//所属势力		
	,attackType(0)//攻击类型ID		
	,skill1(0)//普通技能1		
	,skill2(0)//普通技能2		
	,skill3(0)//普通技能3		
	,skill4(0)//普通技能4		
	,skill5(0)//普通技能5		
	,skill6(0)//起跳技能6		
	,skill11(0)//跳起技能11		
	,skill7(0)//必杀技能7		
	,skill8(0)//必杀技能8		
	,skill9(0)//必杀技能9		
	,skill10(0)//连携技能10		
	,skill12(0)//防御技能12		
	,moveSpeed(0)//基础移动速度		
	,sight(0)//警戒范围		
	,karma1(0)//缘分1		
	,karma2(0)//缘分2		
	,seq(0)//显示顺序		
	,initialStar(0)//初始星级		
	,fireCoin(0)//被辞退给铜钱		
	,resource("")//资源素材		
	,resourceHighShifting(0)//资源高度偏移		
	,resourceShifting(0)//资源左右偏移		
	,resourceRun("")//行走资源素材		
	,dieVoice("")//死亡音效		
	,aiId(0)//AI选择		
	,delayTime(0)//动作间隔		
	,ssTime(0)//免疫时间		
	,attackEvaluate(0)//攻击评价		
	,defenseEvaluate(0)//防御评价		
	,techniquesEvaluate(0)//技巧评价		
	,halfbodyrResource("")//半身像资源		
	,headResource("")//头像资源		
	{};

	int id;
	string name;
	int sex;
	int force;
	int attackType;
	int skill1;
	int skill2;
	int skill3;
	int skill4;
	int skill5;
	int skill6;
	int skill11;
	int skill7;
	int skill8;
	int skill9;
	int skill10;
	int skill12;
	short moveSpeed;
	short sight;
	short karma1;
	short karma2;
	short seq;
	short initialStar;
	int fireCoin;
	string resource;
	short resourceHighShifting;
	short resourceShifting;
	string resourceRun;
	string dieVoice;
	int aiId;
	int delayTime;
	int ssTime;
	short attackEvaluate;
	short defenseEvaluate;
	short techniquesEvaluate;
	string halfbodyrResource;
	string headResource;
};
#endif
