#ifndef __DictSkill__
#define __DictSkill__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictSkill:public Ref
{
public:
	DictSkill():	
	id(0)//ID		
	,name("")//名称		
	,ename("")//英文名称		
	,desc("")//技能描述		
	,type(0)//技能类型		
	,attackType(0)//攻击类型ID		
	,costWay(0)//技能释放方式		
	,coldDowm(0)//技能冷却时间		
	,costRage(0)//技能消耗怒气		
	,target(0)//技能目标类型		
	,knockDown(0)//技能是否击倒		
	,knockFly(0)//技能是否击飞		
	,actionHurt(0)//是否播放受伤动作		
	,flashMove(0)//角色瞬移距离		
	,beatBack(0)//技能击退格数		
	,hurtBackward(0)//后方伤害范围		
	,hurtForward(0)//前方伤害范围		
	,hurtHigh(0)//技能伤害高度		
	,hurtEffectTimes(0)//技能效果次数		
	,heroShiftBackward(0)//角色后方位移		
	,heroShiftForward(0)//角色前方位移		
	,moveTime(0)//技能动作时间		
	,effectBlastBackward(0)//技能特效后方冲击破		
	,effectBlastForward(0)//技能特效前方冲击破		
	,effectPositionBackward(0)//技能特效后方定点		
	,effectPositionForward(0)//技能特效前方定点		
	,effectRangeBackward(0)//技能特效后方射程		
	,effectRangeForward(0)//技能特效前方射程		
	,resourceHighShifting(0)//资源高度偏移		
	,nameResource("")//技能名称资源地址		
	,flyResource("")//飞行特效		
	,flyResourceTime(0)//飞行特效时间		
	,flyRLoopMarker(0)//飞行特效循环标记		
	,hitResource("")//受击特效		
	,hitHighShifting(0)//受击特效高度偏移		
	,fullScreen("")//全屏特效		
	,icon("")//icon		
	,damagePower1(0)//战斗伤害倍率1		
	,damagePower2(0)//战斗伤害倍率2		
	,isTurn(0)//是否可转身		
	,damageNumber(0)//战斗伤害个数		
	,toBuffId("")//对应BuffID		
	,buffOdds(0)//buff触发几率		
	,soundUse("")//施法音效		
	,soundFly("")//飞行音效		
	,soundHit("")//受击音效		
	,colorHit("")//受击颜色		
	{};

	int id;
	string name;
	string ename;
	string desc;
	int type;
	int attackType;
	int costWay;
	short coldDowm;
	short costRage;
	int target;
	short knockDown;
	short knockFly;
	short actionHurt;
	short flashMove;
	short beatBack;
	short hurtBackward;
	short hurtForward;
	short hurtHigh;
	short hurtEffectTimes;
	short heroShiftBackward;
	short heroShiftForward;
	double moveTime;
	short effectBlastBackward;
	short effectBlastForward;
	short effectPositionBackward;
	short effectPositionForward;
	short effectRangeBackward;
	short effectRangeForward;
	short resourceHighShifting;
	string nameResource;
	string flyResource;
	float flyResourceTime;
	short flyRLoopMarker;
	string hitResource;
	short hitHighShifting;
	string fullScreen;
	string icon;
	int damagePower1;
	int damagePower2;
	short isTurn;
	short damageNumber;
	string toBuffId;
	int buffOdds;
	string soundUse;
	string soundFly;
	string soundHit;
	string colorHit;
};
#endif
