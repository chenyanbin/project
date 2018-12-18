//
//  LimitCardLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/12/24.
//
//

#ifndef __FightPass__LimitCardLayer__
#define __FightPass__LimitCardLayer__

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../BaseLayer.h"
#include "../data/BaseTypeData.h"
#include "../awardBox/AwardBox_Layer.h"
USING_NS_CC_EXT;
USING_NS_CC;
class LimitCardLayer:public BaseLayer
{
public:
    LimitCardLayer();
    ~LimitCardLayer();
    virtual void onExit();
    virtual void onEnter();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual bool init();
    static LimitCardLayer* create();
    static void show();
private:
    void createLayer();
    void onClick(Ref* pSender);
    void setItemPic(ValueVector &m_skillList);
    void onClickSkill(Ref* pSender);
    
    virtual void backScene();
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    
    void requestlimitCardMsg();
    void onlimitCardProcess(EventCustom* msg);
    void addEventListener();
    void removeEventListener();
    
    void requestChoseCardMsg(int _costType);
    void onChoseCardProcess(EventCustom* msg);
    
private:
    float sx;
    int m_herodictid;
    int m_heroAttackType;//攻击类型
    string m_heroName;//被卡武将名称
    int m_heroHp;//被卡武将血量
    int m_herodefend;//被卡武将防御
    int m_heroAttact;//被卡攻击力
    int m_onecost;//抽卡一次花费元宝数
    int m_tencost;//抽卡十次花费元宝数
    int TAG_BTNONE;//凑一次
    int TAG_BTNTEN;//凑十次
    int m_skill1;
    int m_skill2;
    int m_skill3;
    int m_skill4;
    long m_activityStartTimes;
    long m_activityEndTimes;
    ValueVector* m_varlist;
    bool m_iscloseScene;
};
#endif /* defined(__FightPass__AwardBox_Layer__) */
