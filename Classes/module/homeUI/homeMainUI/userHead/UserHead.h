//
//  UserHead.h
//  SuiTang
//
//  Created by mac on 14-6-8.
//
//

#ifndef __SuiTang__UserHead__
#define __SuiTang__UserHead__

#include "cocos2d.h"
USING_NS_CC;

class UserHead:public Node
{
public:
    UserHead();
    ~UserHead();
    virtual bool init();
    CREATE_FUNC(UserHead);

private:
  
    void setHeadInfo();
    void onHeadClick(Ref* pSender);
    void onVipdClick(Ref* pSender);
    
    void updateVip(EventCustom* msg = NULL);
    void updateUserExp();//更新经验
    void updatePower();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    void updateUserLevel(EventCustom* msg);
    void updateUserName(EventCustom* msg);
private:
    int sx;
    int TAG_LEVEL_LABEL;
    int TAG_VIP_LABEL;
    int TAG_EXPERENCE;
    int TAG_EXPERENCE_LABEL;
    int TAG_VIPBTN;
    int TAG_HEADBG;
    int TAG_FIGHTPOWER;
    int TAG_BG;
    int TAG_EXPPROGRESS;
    int TAG_NAME;
    int TAG_POWER;
    int TAG_EFFECT;
    
    
};

#endif /* defined(__SuiTang__UserHead__) */
