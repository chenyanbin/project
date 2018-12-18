//
//  ArenaListData.h
//  FightPass
//
//  Created by chenyanbin on 16/3/14.
//
// 列表页 排行榜

#ifndef ArenaListData_h
#define ArenaListData_h

#include "cocos2d.h"
USING_NS_CC;
using namespace std;

struct HeroHead
{
    int herodict;//武将dictid
};

class ArenaListData:public Ref
{
public:
    ArenaListData()
    :rank(0)
    ,roleId(0)
    ,heroDictId(0)
    ,roleName("")
    ,power(0)
    ,roleLevel(0)
    ,honor(0)
    ,coin(0)
    {
        
    }
    ~ ArenaListData()
    {
        
    }
    int rank;//排名
    long roleId;//角色ID
    int heroDictId ;//头像ID
    string roleName;//角色昵称
    int power;//	战斗力	int
    int roleLevel;//角色等级
    int honor;//根据排名获得的荣誉奖励
    int coin;//根据排名获得的铜币奖励
    vector<HeroHead> heroHeadList;
    
    
};


#endif /* ArenaListData_h */
