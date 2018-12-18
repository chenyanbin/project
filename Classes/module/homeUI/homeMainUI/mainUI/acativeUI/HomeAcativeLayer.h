//
//  HomeAcativeLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/10/23.
//
//

#ifndef __FightPass__HomeAcativeLayer__
#define __FightPass__HomeAcativeLayer__

#include "cocos2d.h"
#include "../../../../BaseLayer.h"
#include "../../../../../common/TouchSprite/Button.h"
USING_NS_CC;

class HomeAcativeLayer:public BaseLayer
{
public:
    HomeAcativeLayer();
    ~HomeAcativeLayer();
    virtual bool init();
    CREATE_FUNC(HomeAcativeLayer);

protected:
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual void addEventListener();
    virtual void removeEventListener();
private:
    
    void setAcativeBtn();
    void onClick(Ref* pSender);
    Button* setButton(const std::string&normalImage);
    
    void onRefreshDot(EventCustom* msg);
private:
    int sx;
    int TAG_QIANDAO;
    int TAG_MAIL;
    int TAG_MARKET;
    int TAG_GIFT;
    int TAG_RECHARGE;
    int TAG_SEVEN;
    int TAG_EXCHANGE;
    int TAG_SEVENACATIVE;//sevenAcative
    int TAG_ACATIVE;//活动
};


#endif /* defined(__FightPass__HomeAcativeLayer__) */
