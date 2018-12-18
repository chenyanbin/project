//
//  MainUI.h
//  FightPass
//
//  Created by 超 顾 on 15/6/4.
//
//

#ifndef __FightPass__MainUI__
#define __FightPass__MainUI__

#include <stdio.h>
#include "cocos2d.h"
#include "../../../BaseLayer.h"

class MainUI:public BaseLayer
{
public:
    MainUI();
    ~MainUI();
    virtual void onExit();
    virtual void onEnter();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual bool init();
    static void show(Node* _parent,int tag);
    CREATE_FUNC(MainUI);
private:
    void setMask();
    void setMenuBar();
    void setUserHead();
    void setUserWealth();
    void setAcativeBtn();
    void setNotice();
    void requestListMsg();
    void onMsgProcess(EventCustom* msg);
    void addEventListener();
    void removeEventListener();
private:
    
    
};
#endif /* defined(__FightPass__MainUI__) */
