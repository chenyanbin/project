//
//  SevendayPageListLayer.hpp
//  FightPass
//
//  Created by chenyanbin on 16/4/12.
//
//

#ifndef SevendayPageListLayer_hpp
#define SevendayPageListLayer_hpp

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../BaseLayer.h"
#include "../../common/comboxBtn/ComboBoxBtn.h"
USING_NS_CC_EXT;
USING_NS_CC;
#include <Vector>
class SevendayPageListLayer:public BaseLayer
{
public:
    enum TAG_PAGELAYER
    {
        TAG_BOON = 0,
        TAG_TESKTYPEONE,
        TAG_TESKTYPETWO,
        TAG_HALF
    };
    SevendayPageListLayer();
    ~ SevendayPageListLayer();
    static SevendayPageListLayer* create(int day);
    virtual bool init( int day);
    
protected:
    virtual void onEnter();
    virtual void onExit();
    virtual void onEnterTransitionDidFinish();
    virtual void onExitTransitionDidStart();
private:
    void setBg();
    void onTopComboBoxClick(Ref* pSender);
    void everyBoonLayer(int tag);
    void setHalfPriceLayer(int tag);
    void setTaskLayer(int tag);
    
    void refreshModuleRedPot();
    void addEventListener();
    void removeEventListener();
private:
    int m_day;
    float sx;
    int m_pageindex;
    bool m_isTeskOne;
    ComboBoxBtn* boxBtn;
    int m_index;
    
    
};

#endif /* SevendayPageListLayer_hpp */
