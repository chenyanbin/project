//
//  RebornPanel.h
//  FightPass
//
//  Created by zhangxiaobin on 15/9/7.
//复活框
//

#ifndef __FightPass__RebornPanel__
#define __FightPass__RebornPanel__

#include "../../BaseLayer.h"
#include "../../../common/Dialog/Dialog.h"
class RebornPanel:public BaseLayer
{
public:
    RebornPanel();
    ~RebornPanel();
    virtual bool init(int rebornCount);
    static RebornPanel* create(int rebornCount);
    static void show(int costGold);
protected:
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
private:
    void setConfirmBtn();
    void onConfirmClick(Ref* pSender);
    void setCancelBtn();
    void onCancelClick(Ref* pSender);
    void onDelay();
    void setTitle();
    int getCostGold(int count);
    void onCancel();
 
    
private:
    int m_rebornCount;
    int m_costGold;
    int m_delayCount;
    int TAG_CONFIRM;
    int TAG_LABEL;
    int TAG_TITLE;
};

#endif /* defined(__FightPass__RebornPanel__) */
