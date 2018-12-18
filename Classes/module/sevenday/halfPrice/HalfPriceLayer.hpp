//
//  HalfPriceLayer.hpp
//  FightPass
//
//  Created by chenyanbin on 16/4/13.
//
//

#ifndef HalfPriceLayer_hpp
#define HalfPriceLayer_hpp


#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../../BaseLayer.h"
USING_NS_CC_EXT;
USING_NS_CC;
#include <Vector>
class HalfPriceLayer:public BaseLayer
{
public:
    HalfPriceLayer();
    ~ HalfPriceLayer();
    static HalfPriceLayer* create(int day);
    virtual bool init( int day);
    
protected:
    virtual void onEnter();
    virtual void onExit();
    virtual void onEnterTransitionDidFinish();
    virtual void onExitTransitionDidStart();
    virtual void addEventListener();
    virtual void removeEventListener();
private:
    void setBackground();
    void sethalfPrive();
    void requestWeekHalfPricePage(int _day);
    void onWeekHalfPriceProcess(EventCustom* msg);
    
    void requesthalfBuyMsg(int _day);
    void onhalfBuyProcess(EventCustom* msg);
    
    void onBuyClick(Ref* pSender);
    void onhalfitemClick(Node* pSender);
private:
    int m_day;
    float sx;
    int TAG_BUYBTN;
    
};


#endif /* HalfPriceLayer_hpp */
