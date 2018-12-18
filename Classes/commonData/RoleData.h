//
//  RoleData.h
//  sanguo
//
//  Created by mac on 14-6-6.
//
//
#ifndef __SuiTang__RoleData__
#define __SuiTang__RoleData__
#include "cocos2d.h"
using namespace std;
USING_NS_CC;
class RoleData:public Ref
{
public:
    RoleData()
    :name("金永哲")
    ,roleID(0)
    ,mainHeroID(0)
    ,mainHeroDictID(0)
    ,experience(0)
    ,combatPower(0)
    ,level(1)
    ,glory(0)
    ,expLoit(0)
    ,headID("")
    ,yayaId(-1)
    ,quality(1)
    {
        
    }
    //角色玩家id
    long long roleID;
    int mainHeroID;
    int mainHeroDictID;//英雄表里的id
    int quality;//品质
    string name;
    int level;
    //性别 1，男，2，女
    unsigned char sex;
    //头像id
    string headID;
    double experience;//经验值
    int combatPower;//战斗力
    
    double glory;
    double expLoit;//军功
    int yayaId;
    
};
#endif