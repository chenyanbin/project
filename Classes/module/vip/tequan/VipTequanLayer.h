//
//  VipTequanLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/10/12.
//
//

#ifndef __FightPass__VipTequanLayer__
#define __FightPass__VipTequanLayer__

#include "cocos2d.h"
#include "../../BaseLayer.h"
#include "../../../commonData/dictData/DictVipGift/DictVipGift.h"
class VipTequanLayer:public BaseLayer
{
public:
    
    VipTequanLayer();
    ~ VipTequanLayer();
    virtual bool init(int _level);
    static VipTequanLayer* create(int _level);
    static void show(int  _level);
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    
private:
    void setButton();
    void leftPage(Ref* psender);
    void rightPage(Ref* psender);
    void setVIPlevel();
    void setGiftHead();
    void onitemClick(Node* pSender);
    void onclick(Ref* pSender);
private:
    Point touchBeginPos;
    int TAG_VIPLEVEL;
    int m_level;//vip等级
    Vector<DictVipGift*>* giftList;//礼包
    int TAG_MINLEVEL;
    int TAG_LEVEL;
    int TAG_ADDLEVEL;
    int TAG_NODE;
    int TAG_DEXLEVEL;
    Vector<DictVipGift*>* giftListitem;//礼包详情


};


#endif /* defined(__FightPass__VipTequanLayer__) */
