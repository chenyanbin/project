//
//  RoleMessageData.h
//  FightPass
//
//  Created by chenyanbin on 16/3/28.
//
//

#ifndef RoleMessageData_h
#define RoleMessageData_h

#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class RoleMessageData:public Ref
{
public:
    RoleMessageData()
    :heroId(0)
    ,heroDictId(0)
    ,force(0)
    ,heroName("")
    ,heroQuality(0)
    ,heroLevel(0)
    ,prestige(0)
    ,combatPower(0)
    ,leadership(0)
    {
        
    }
    ~ RoleMessageData()
    {
        
    }
    int heroId;//	武将id	int	Y
    int heroDictId;//	武将dict id	int	Y
    int force;//	势力	byte	Y
    string heroName;//	武将名称	string	Y
    int heroQuality;//	武将品质	byte	Y
    int heroLevel;//	武将等级	int	Y
    int prestige;//	武将声望	int	Y
    int combatPower;//	武将战斗力	int	Y
    int leadership;//	武将领导力	int	Y
    
    
};

#endif /* RoleMessageData_h */
