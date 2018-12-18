//
//  SevendayChoseHeroLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/11/27.
//
//

#ifndef __FightPass__SevendayChoseHeroLayer__
#define __FightPass__SevendayChoseHeroLayer__

#include "../../BaseLayer.h"
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
USING_NS_CC_EXT;
USING_NS_CC;
#include "../../data/BaseTypeData.h"
class SevendayChoseHeroLayer:public BaseLayer
{
public:
    enum TAG_BTN
    {
        TAG_ADD = 10,
        TAG_ADDTEN,
        TAG_MINUS,
        TAG_MINUSTEN
    };
    SevendayChoseHeroLayer();
    ~ SevendayChoseHeroLayer();
    virtual bool init(int idx);
    static SevendayChoseHeroLayer* create(int idx);
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
    void onMsgProcess(EventCustom* msg);
    virtual void addEventListener();
    virtual void removeEventListener();
    void requestListMsg(int shopId );//发送购买信息
private:
    int m_type;
    int TAG_NODE;
    int TAG_USERHEAD;
    int m_numHero;//选择第几个英雄
    
    Vector<BaseTypeData*>* m_baseList;
    
};


#endif /* defined(__FightPass__SevendayChoseHeroLayer__) */
