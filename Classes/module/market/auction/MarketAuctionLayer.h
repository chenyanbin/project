//
//  MarketAuctionLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/8/28.
//
//  拍卖

#ifndef __FightPass__MarketAuctionLayer__
#define __FightPass__MarketAuctionLayer__

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../../BaseLayer.h"
USING_NS_CC_EXT;
USING_NS_CC;

class MarketAuctionLayer:public BaseLayer{
public:
    enum tag_layer
    {
        TAG_PAIMAISUO = 10,
        TAG_QUCHUSHOU,
        TAG_SHANGJIAZHONG
    };
    MarketAuctionLayer();
    ~MarketAuctionLayer();
    static MarketAuctionLayer* create();
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    void onEnterTransitionDidFinish();
    void onExitTransitionDidStart();
private:
    void setBackGround();
    void onTopComboBoxClick(Ref * psender);
    void setPaimaisuo();
    void setQuchushou();
    void setShangjiazhong();
    void onSerchBtn(Ref* psender);
    void setEditBox();//输入框
    void requestAuctionHomeListMsg(const char* itemName,int lastSellId);
    
private:
    Sprite* listBg;
    int m_layer;
    EditBox* editbox;
    int TAG_LISTBG;
    int TAG_SERCH;
 
};

#endif /* defined(__FightPass__MarketAuctionLayer__) */
