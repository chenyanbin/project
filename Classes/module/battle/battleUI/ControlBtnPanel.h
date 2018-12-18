//
//  ControlBtnPanel.h
//  FightPass
//
//  Created by chenyanbin on 15/6/9.
//控制面板 技能释放操作
//

#ifndef __FightPass__ControlBtnPanel__
#define __FightPass__ControlBtnPanel__

#include "../../BaseLayer.h"
USING_NS_CC;
#include "../../../common/TouchSprite/TouchSprite.h"
#include "../../../avatar/hero/Hero.h"
#define COMMON_CD_TIME 1 //1秒公共cd时间
class ControlBtnPanel:public BaseLayer
{
public:
    enum
    {
        BUTTON_SKILL1 = 1,
        BUTTON_SKILL2 = 2,
        BUTTON_SKILL3 = 3,
        BUTTON_SKILL4 = 4,//跳跃
        BUTTON_ATTACK = 5,
        BUTTON_PROTECTED = 6//防御或闪避
    };
    ControlBtnPanel();
    ~ControlBtnPanel();
    bool init(const ccMenuCallback& callback,const ccMenuCallback& releaseCallBack = NULL);
    static ControlBtnPanel* create(const ccMenuCallback& callback,const ccMenuCallback& releaseCallBack = NULL);
    void onSkill1CD(float time,bool isCommonCD = true);
    void onSkill2CD(float time,bool isCommonCD = true);
    void onSkill3CD(float time,bool isCommonCD = true);
    void onSkill4CD(float time,bool isCommonCD = true);
    void onSkill5CD(float time,bool isCommonCD = true);
    
    
    void showSkill1(EventCustom* msg );
    void showSkill2(EventCustom* msg );
    void showSkill3(EventCustom* msg );
    void showProtectedBtn(EventCustom* msg );
    
    void reset(Hero* mainHero);
protected:
    virtual void onEnter();
    virtual void onExit();
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
private:
    void setBg();
    void setButton();
    void onButtonClick(Node* pSender);
    void playCommonCD(Node* target);
    void onTimeDelay(Node* target,float time);
    void onButtonRelease(Node* pSender);
private:
    Hero* m_MainHero;
    ccMenuCallback m_callBack;
    ccMenuCallback m_releaseBack;
    Point m_beginPostion;
    bool m_isMoveing;
    bool m_isInited;
    int TAG_CD;
    int TAG_CDLABEL;
    int handMoveFlag;//手势移动标志
};

#endif /* defined(__FightPass__ControlBtnPanel__) */
