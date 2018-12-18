//
//  VipHeadGiftLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/10/30.
//
//

#ifndef __FightPass__VipHeadGiftLayer__
#define __FightPass__VipHeadGiftLayer__

#include "cocos2d.h"
#include "../../BaseLayer.h"
#include "../../../commonData/dictData/DictVipGift/DictVipGift.h"
class VipHeadGiftLayer:public BaseLayer
{
public:
    
    VipHeadGiftLayer();
    ~ VipHeadGiftLayer();
    virtual bool init(int _level);
    static VipHeadGiftLayer* create(int _level);
    static void show(int  _level);
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    
       
private:
    void setVIPlevel();
    void setGiftHead();
    void onitemClick(Node* pSender);
private:
    Point touchBeginPos;
    int TAG_VIPLEVEL;
    int m_level;//vip等级
    Vector<DictVipGift*>* giftList;//声望
    int TAG_MINLEVEL;
    int TAG_LEVEL;
    int TAG_ADDLEVEL;
    int TAG_NODE;
    int TAG_DEXLEVEL;
    Vector<DictVipGift*>* giftListitem;//礼包详情
    
    
};


#endif /* defined(__FightPass__VipHeadGiftLayer__) */
