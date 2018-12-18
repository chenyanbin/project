#ifndef __DictRoleLevel__
#define __DictRoleLevel__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class DictRoleLevel:public Ref
{
public:
	DictRoleLevel():	
	playerLevel(0)//等级		
	,needExp(0)//升级需要的经验		
	,leadership(0)//领导力上限		
	,heroBelongUp(0)//携带武将基础上限		
	,equipBelongUp(0)//携带装备基础上限		
	,stageBattleExp(0)//关卡经验		
	,stageBattleCoin(0)//关卡铜钱		
	,arenaBattleExp(0)//PVP战斗经验		
	,arenaBattleCoin(0)//PVP战斗铜钱		
	,arenaBattleGlory(0)//PVP获得战功		
	,powerRecoverLimit(0)//自动恢复体力上限		
	,powerBonus(0)//升级增加当前体力		
	,openFunction(0)//开启功能ID		
	{};

	short playerLevel;
	int needExp;
	short leadership;
	short heroBelongUp;
	short equipBelongUp;
	int stageBattleExp;
	int stageBattleCoin;
	int arenaBattleExp;
	int arenaBattleCoin;
	int arenaBattleGlory;
	short powerRecoverLimit;
	short powerBonus;
	short openFunction;
};
#endif
