//
//  SevenActivity_Layer.h
//  FightPass
//
//  Created by 超 顾 on 15/10/19.
//
//

#ifndef __FightPass__SevenActivity_Layer__
#define __FightPass__SevenActivity_Layer__

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../../BaseLayer.h"
USING_NS_CC_EXT;
USING_NS_CC;
class SevenActivity_Layer:public BaseLayer
{
public:
    SevenActivity_Layer();
    ~SevenActivity_Layer();
    virtual void onExit();
    virtual void onEnter();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual bool init();
    static SevenActivity_Layer* create();
private:
    void createLayer();
    void onComboBoxBtnClick(Ref* psender);
    
    void requestWeekDayMsg();
    void onWeekDayMsgProcess(EventCustom* msg);
    void addEventListener();
    
    void requestWeekRewardPage(int _day);
    void onWeekRewardProcess(EventCustom* msg);
    
    void requestWeekHalfPricePage(int _day);
    void onWeekHalfPriceProcess(EventCustom* msg);
private:
    float sx;
    int TAG_SEVENDAY;
    int m_someDay;//第几天 查看第几天内容
    int m_day;//第几天服务器
    int TAG_BOXBTN;
};

#endif /* defined(__FightPass__SevenActivity_Layer__) */
