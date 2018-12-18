//
//  homeScene.h
//  FightPass
//
//  Created by 超 顾 on 15/6/2.
//
//

#ifndef __FightPass__homeScene__
#define __FightPass__homeScene__

#include <stdio.h>
#include "../BaseLayer.h"
#include "homeMap/HomeMapUI.h"
#include "../battle/simplePad/SimplePad.h"
class HomeScene:public BaseLayer
{
public:
    HomeScene();
    ~HomeScene();
    virtual bool init();
    static Scene* showScene(int fromeScene);
    CREATE_FUNC(HomeScene);
private:
    void addHomeMap();
    void addSimplePad();
    void addMainUI();
    void addChat();
    void onYaYaChanelLoginCallBack(EventCustom* msg);
protected:
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
//    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
//    virtual void onTouchMoved(Touch *touch, Event *unused_event);
//    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    
private:
    HomeMapUI* homeBgMap;
    SimplePad* m_simplePad;
};

#endif /* defined(__FightPass__homeScene__) */
