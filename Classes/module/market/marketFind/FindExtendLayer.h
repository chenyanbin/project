//
//  FindExtendLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/9/1.
//
// 创建新领地弹出层

#ifndef __FightPass__FindExtendLayer__
#define __FightPass__FindExtendLayer__

#include "../../BaseLayer.h"
class FindExtendLayer:public BaseLayer
{
public:

    FindExtendLayer();
    ~FindExtendLayer();
    virtual bool init(int nextExtentGold);
    static FindExtendLayer* create(int nextExtentGold);
    static void show(int nextExtentGold);
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
private:
    void setUiSpr();
    void setSureBuyBtn();
    void onSureBuyClick(Ref* psender);
    void onCencelClick(Ref* psender);
    void requestExtendMsg();//请求创建新领地
    void onExtendMsgProcess(EventCustom* msg);
    void addEventListener();
    void removeEventListener();
    void removeRequestfindlistMsg();
private:
    int m_nextExtentGold;//扩展需要元宝
};


#endif /* defined(__FightPass__FindExtendLayer__) */
