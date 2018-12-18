//
//  juxianWindowLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/9/7.
//
//

#ifndef __FightPass__juxianWindowLayer__
#define __FightPass__juxianWindowLayer__

#include "cocos2d.h"
#include "../../BaseLayer.h"
#include "../marketData/JuxianListData.h"
class juxianWindowLayer:public BaseLayer
{
public:
    
    juxianWindowLayer();
    ~juxianWindowLayer();
    virtual bool init(int tpye, int idx);
    static juxianWindowLayer* create(int type, int idx);
    static void show(int type, int idx);
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    
private:
    void setButton();
    void onSureBuyClick(Ref* psender);
    void onCencelClick(Ref* psender);
    void setjuxianType(int type);
    void setqiuxianruoke();
    void setlixianxiashi();
    void setweocaishiju();
    void setOrderCard( JuxianListData* data);
    void requesttimesMsg(int leadId, int countMode);
private:
    int m_type;
    int m_ownGold;//
    int m_idx;//第一次或者十连抽
    int TAG_MILITARY;
};


#endif /* defined(__FightPass__juxianWindowLayer__) */
