//
//  BuyTimeLayer.hpp
//  FightPass
//
//  Created by chenyanbin on 16/3/29.
//
//

#ifndef BuyTimeLayer_hpp
#define BuyTimeLayer_hpp

#include "../../BaseLayer.h"
class BuyTimeLayer:public BaseLayer
{
public:
    BuyTimeLayer();
    ~ BuyTimeLayer();
    virtual bool init(int buytype,int glod,int time = 0);
    static BuyTimeLayer* create(int buytype,int glod,int time = 0);
    static void show(int buytype,int glod,int time = 0);
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
private:
    void setBgLayer();
    
    void requestBuyTimeMsg(int buyType);//请求开始寻访
    void onBuyTimeMsgProcess(EventCustom* msg);
    void addEventListener();
    void removeEventListener();
    void setSureBuyBtn();
    void onSureBuyClick(Ref* psender);
    void onCencelClick(Ref* psender);
    
private:
    int m_buytype;//购买类型
    int m_glod;//元宝
    int m_times;//次数
};


#endif /* BuyTimeLayer_hpp */
