//
//  BossBloodManager.h
//  FightPass
//
//  Created by zhangxiaobin on 15/7/24.
//
//

#ifndef __FightPass__BossBloodManager__
#define __FightPass__BossBloodManager__

#include "cocos2d.h"
USING_NS_CC;
#include "../../../avatar/monster/Monster.h"
class BossBloodManager:public Node
{
public:
    static BossBloodManager* getInstance();
    void updateBoss(Monster* monster);
    void updateBlood();
private:
    void setBlood();
    void setHalfBody();
    void setName();
private:
    BossBloodManager();
    ~BossBloodManager();
    static BossBloodManager* _instance;
    Monster* m_boss;
private:
    int TAG_PROGRESS;
    int TAG_HEAD;
    int TAG_NAME;
};

#endif /* defined(__FightPass__BossBloodManager__) */
