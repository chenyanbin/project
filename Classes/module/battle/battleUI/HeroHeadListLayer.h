//
//  HeroHeadListLayer.h
//  FightPass
//
//  Created by zhangxiaobin on 15/7/8.
//
//

#ifndef __FightPass__HeroHeadListLayer__
#define __FightPass__HeroHeadListLayer__

#include "cocos2d.h"
USING_NS_CC;
#include "../../../avatar/hero/Hero.h"
#include "../../../common/commonEffect/CommonEffect.h"
class HeroHead;
class HeroHeadListLayer:public Node
{
public:
    void removeHero(Hero* hero);
    void addHero(Hero* hero);
    void onHeroHurt(int heroUID,float damage);//英雄减血
    void onHeroAddBlood(int heroUID,float value);//英雄加血
    static HeroHeadListLayer* getInstance();
    void updateList(HeroHead* mainHead);
    void updateHeroPostion(HeroHead* mainHead);
    void clear();
    void setClickEnable(bool enable);
    bool getClickEnable();
    void setBlood(float m_curBlood,float m_totalBlood);//更新血量
    void resetBlood();
    void onReborn();//重生
    void updateBloodbottle(int count);//更新血瓶
    void showBloodEffect();
    void hideBloodEffect();
    void updateMainHero(Hero* hero);
    void addBuff(int heroID,int buffID);
   
private:
    void updateProgressText(float percent);
    void setHeroBlood();
    void addHead(HeroHead* head);
    
    HeroHeadListLayer();
    ~HeroHeadListLayer();
    void onBottleClick(Node* pSender);
    float m_totalBlood;
    float m_curBlood;
    int m_bottleCount;
    Vector<Hero*>* heroList;
    bool m_isClickEnable;//是否可以点击
    ProgressTimer* bloodProgress;
    static HeroHeadListLayer* _instance;
    Node* headContainer;
    Label* m_bottleLabel;
    CommonEffect* headEffect;

private:
    int TAG_BOTTLE;
    int TAG_BOTTLEEFFECT;
    int TAG_PROGRESSTXT;
    
  
};
class HeroHead:public Node
{
public:
    HeroHead();
    ~HeroHead();
    virtual bool init(Hero* hero);
    static HeroHead* create(Hero* hero);
    //受伤
    void onHeroHurt();
    void onHeroAddBlood(float value);
    void resetBlood();
    void onReborn();//重生
    Hero* getHero();
    void addBuff(int buffID);
    void setBloodVisible(bool visible);
    void removeBuff(int buffType);
    void addBlackMask();
private:
    void sethead();
    void onHeadTouch(Node* target);
    void hideServerLoading();
private:
    Hero* m_hero;
    float m_totalBlood;//初始血量
    float m_nowBlood;//当前血量
    ProgressTimer* bloodPt;
    Node* buffContainer;
private:
    int TAG_BLOOD_PROGRESS;
    int TAG_BLACKMASK;
    int TAG_HEAD;
    int TAG_FORM;
   
};

#endif /* defined(__FightPass__HeroHeadListLayer__) */
