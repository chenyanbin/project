//
//  RankingData.h
//  FightPass
//
//  Created by chenyanbin on 16/1/11.
//
//

#ifndef RankingData_h
#define RankingData_h

#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class RankingData: public Ref
{
public:
    RankingData()
    :roleName("")
    ,userId(0)
    ,iconHeroDictId(0)
    ,roleLevel(0)
    ,combatPowe(0)
    ,scoreToday(0)
    {
        
    }
//    virtual void release()
//    {
//        Ref::release();
//    }
     ~RankingData()
    {
        
    }
    string roleName;//角色名称
    long userId;//角色Id
    int iconHeroDictId;//角色头像
    int roleLevel;//角色等级
    int combatPowe;//战斗力
    int scoreToday;//分数
    
};
#endif /* RankingData_h */
