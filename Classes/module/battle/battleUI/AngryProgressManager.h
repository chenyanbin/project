//
//  AngryProgressManager.h
//  FightPass
//
//  Created by zhangxiaobin on 15/9/19.
//怒气条进度管理
//

#ifndef __FightPass__AngryProgressManager__
#define __FightPass__AngryProgressManager__

#include "cocos2d.h"
USING_NS_CC;
#include "../../../avatar/hero/Hero.h"
#define TOTAL_ANGRY_VALUE 200
class AngryProgressManager:public Node
{
public:
    static AngryProgressManager* getInstance();
    void updateMainHero(Hero* hero);
    void updateAngryValue();
    bool isGuided;//是否已经引导过了。
private:
    void setProgress();
    void setAngryBtn();
    void onBtnClick(Node* psender);
    void onProgressClick(Node* pSender);
    void showAngryEffect();
    void onEffectLoaded(float percent);
private:
    ProgressTimer* progressTimer;
    AngryProgressManager();
    ~AngryProgressManager();
    static AngryProgressManager* _instance;
    Hero* m_hero;
    bool isAngry;//怒气是否已满
  
private:
    int TAG_ANGRYEFFECT_BACK;
    int TAG_ANGRYEFFECT_FRONT;
    int TAG_SKLLBTN;
};

#endif /* defined(__FightPass__AngryProgressManager__) */
