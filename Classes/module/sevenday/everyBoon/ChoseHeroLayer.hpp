//
//  ChoseHeroLayer.hpp
//  FightPass
//
//  Created by chenyanbin on 16/4/15.
//
//

#ifndef ChoseHeroLayer_hpp
#define ChoseHeroLayer_hpp

#include "../../BaseLayer.h"
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
USING_NS_CC_EXT;
USING_NS_CC;

class ChoseHeroLayer:public BaseLayer
{
public:
    enum TAG_BTN
    {
        TAG_ADD = 10,
        TAG_ADDTEN,
        TAG_MINUS,
        TAG_MINUSTEN
    };
    ChoseHeroLayer();
    ~ ChoseHeroLayer();
    virtual bool init(int idx);
    static ChoseHeroLayer* create(int idx);
    static void show(int idx);
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
private:
    void setButton();
    void setSureBuyBtn();
    void onCencelClick(Ref* psender);
    void onSureBuyClick(Ref* psender);
    void onitemClick(Node* pSender);
    
private:
    int m_type;
    int TAG_NODE;
    int TAG_USERHEAD;
    int m_numHero;//选择第几个英雄
    
    
};

#endif /* ChoseHeroLayer_hpp */
