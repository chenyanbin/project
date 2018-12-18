//
//  FindAccelerationLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/9/1.
//
//  确认加速层弹出层

#ifndef __FightPass__FindAccelerationLayer__
#define __FightPass__FindAccelerationLayer__

#include "../../BaseLayer.h"
class FindAccelerationLayer:public BaseLayer
{
public:
    FindAccelerationLayer();
    ~FindAccelerationLayer();
    virtual bool init(int idx);
    static FindAccelerationLayer* create(int idx);
     static void show(int idx);
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
private:
    void setUiSpr();
    void setSureBuyBtn();
    void onSureBuyClick(Ref* psender);
    void onCencelClick(Ref* psender);
    
    void requestAccelerMsg(int findId);//请求开始寻访
    void onAccelerMsgProcess(EventCustom* msg);
    void addEventListener();
    void removeEventListener();
    
   private:
    int m_nowcount;
    int TAG_COUNT;
    int TAG_ALLCOUNT;
    int m_idx;
    int m_owngold;//总元宝
    
    
};


#endif /* defined(__FightPass__FindAccelerationLayer__) */
