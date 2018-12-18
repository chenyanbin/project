//
//  FamouseReset.hpp
//  FightPass
//
//  Created by zhangxiaobin on 16/2/1.
//次数重置
//

#ifndef FamouseReset_hpp
#define FamouseReset_hpp

#include "../../BaseLayer.h"
class FamouseReset:public BaseLayer
{
public:
    FamouseReset();
    ~FamouseReset();
    virtual bool init(int attackCount);
    static FamouseReset* create(int attackCount);
    
    static void show(int attackCount);
private:
    
    void onMsgProcess(EventCustom* message);
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual void addEventListener();
    virtual void removeEventListener();
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
private:
    void onBtnClick(Node* pSender);
    void setContent();
    void setCardIcon();
private:
    
    int ID_CHALLENGECARD_ID;
    int m_attackCount;;;;//剩余挑战次数
    
    int TAG_ICON;
};

#endif /* FamouseReset_hpp */
