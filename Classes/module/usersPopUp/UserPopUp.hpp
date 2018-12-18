//
//  UserPropUp.hpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/9.
//
//

#ifndef UserPopUp_hpp
#define UserPopUp_hpp
#include "../BaseLayer.h"
#include "../../soundManager/SoundManager.h"
class UserPopUp:public BaseLayer
{
public:
    UserPopUp();
    ~UserPopUp();
    
    static void showLevel(int newLevel);
    static void showNewFunctionOpen(int functionID);
protected:
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    
    
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual void delayClickClose();
protected:
    void setClickClose();
};

#endif /* UserPropUp_hpp */
