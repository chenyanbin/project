//
//  BossNode.hpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/7.
//
//

#ifndef BossNode_hpp
#define BossNode_hpp

#include "cocos2d.h"
USING_NS_CC;
#include "FamouseFightGo.hpp"
class BossNode:public Node
{
public:
    BossNode();
    ~BossNode();
    static BossNode* create(FamouseBossData* data);
    bool init(FamouseBossData*);
private:
    void setHead();
    void setName();
    void setDelayTime();//倒计时行
    void setBloodPercent();
    void setButton();
    void onBtnClick(Ref* pSender);
    void onDelay();
protected:
    void onEnter();
    void onExit();
private:
    FamouseBossData* m_data;
    int TAG_DELAYTIME;
};

#endif /* BossNode_hpp */
