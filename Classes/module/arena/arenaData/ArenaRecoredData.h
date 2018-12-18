
//
//  ArenaRecoredData.h
//  FightPass
//
//  Created by chenyanbin on 16/3/17.
//
//  战斗记录

#ifndef ArenaRecoredData_h
#define ArenaRecoredData_h
#include "cocos2d.h"
USING_NS_CC;
using namespace std;


class ArenaRecoredData:public Ref
{
public:
    ArenaRecoredData()
    :lineupPower(0)
    ,heroDictId(0)
    ,roleName("")
    ,roleLevel(0)
    ,isWin(0)
    ,upOrDown(0)
    ,challengeTime(0)
    {
        
    }
    ~ ArenaRecoredData()
    {
        
    }
    int lineupPower;//阵容战斗力
    int heroDictId;//	被挑战者的头像	int
    string roleName;//	被挑战者的角色名	string
    int roleLevel;//	被挑战者的角色等级	int
    int isWin;//	是否挑战成功	byte
    int upOrDown;//	排名变化情况	byte
    long challengeTime;//	挑战时间	long
    
    
};

#endif /* ArenaRecoredData_h */
