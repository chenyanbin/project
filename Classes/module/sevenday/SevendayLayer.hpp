//
//  SevendayLayer.hpp
//  FightPass
//
//  Created by chenyanbin on 16/4/12.
//
//

#ifndef SevendayLayer_hpp
#define SevendayLayer_hpp

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../BaseLayer.h"
#include "../../common/comboxBtn/ComboBoxBtn.h"
USING_NS_CC_EXT;
USING_NS_CC;
class SevendayLayer:public BaseLayer
{
public:
    enum TAG_LAYER
    {
        TAG_ONETAY = 1,
        TAG_TWODAY,
        TAG_THREEDAY,
        TAG_FOURDAY,
        TAG_FIVEDAY,
        TAG_SIXDAY,
        TAG_SEVENDAY
    };
    SevendayLayer();
    ~ SevendayLayer();
    static SevendayLayer* create(int day);
    static void show(int fromeScene = -1,int day = 1);
protected:
    virtual void onExit();
    virtual void onEnter();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual bool init(int day);
    virtual void addEventListener();
    virtual void removeEventListener();
protected:
    void createLayer();
    void topLayer();
    void setRightBtn();
    void onRightBtnClick(Ref* pSender);
    void setPageList(int day);
    
    void requestWeekDayMsg();
    void onWeekDayMsgProcess(EventCustom* msg);
    
    void requestWeekRedPotPage();
    void onWeekRedPotProcess(EventCustom* msg);
   
    void refreshRedPot(EventCustom* msg);

private:
    float sx;
    ComboBoxBtn* boxBtn;
    int m_dayIndex;
    int m_realDay;
};

#endif /* SevendayLayer_hpp */
