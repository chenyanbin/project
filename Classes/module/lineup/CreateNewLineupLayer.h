//
//  CreateNewLineupLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/9/16.
//
//

#ifndef __FightPass__CreateNewLineupLayer__
#define __FightPass__CreateNewLineupLayer__

#include "cocos2d.h"
#include "../BaseLayer.h"
class CreateNewLineupLayer:public BaseLayer
{
public:
    
    CreateNewLineupLayer();
    ~CreateNewLineupLayer();
    virtual bool init(int coust, int AllPage);
    static CreateNewLineupLayer* create(int coust, int AllPage);
    static void show(int coust, int AllPage);
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    
private:
    void setButton();
    void onSureBuyClick(Ref* psender);
    void onCencelClick(Ref* psender);
    void requestCreateMsg();
    virtual void addEventListener();
    virtual void removeEventListener();
    void onCreateNewLineup(EventCustom* msg);
private:
    int m_nextConsume;
    int m_allGold;//角色拥有的元宝
    int m_AllPage;//当前整容数量
};


#endif /* defined(__FightPass__CreateNewLineupLayer__) */
