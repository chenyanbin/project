//
//  ExperienceEffect.h
//  FightPass
//
//  Created by 超 顾 on 15/10/15.
//
//

#ifndef __FightPass__ExperienceEffect__
#define __FightPass__ExperienceEffect__

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../../BaseLayer.h"
#include "../data/CardPropertyData.h"
USING_NS_CC_EXT;
USING_NS_CC;
class ExperienceEffect:public BaseLayer
{
public:
    ExperienceEffect();
    ~ExperienceEffect();
    virtual void onExit();
    virtual void onEnter();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual bool init(CardPropertyData* _ago,CardPropertyData* _after);
    static ExperienceEffect* create(CardPropertyData* _ago,CardPropertyData* _after);
private:
    void startLayer();
    void createLayer();
    void loadPerson();
    void onLeveUpEffect();
    void onDataLoaded(float percent);
    void clearResourcePerson(string str);
    void experEffect();
    void showExperienceSound();
    void deleteActionInterval(Node* pSprite,Vector<ActionInterval*> *actionInterval);
    void completeScale();
private:
    int TAG_CARDBG;
    int TAG_LEVELABEL;
    int TAG_MAXLEVELABEL;
    int TAG_NAMELABEL;
    int TAG_PRESTLABEL;
    int TAG_MILITLABEL;
    int TAG_PROGRESS;
    int TAG_LEADLABEL;
    
    string cardName;
    float sx;
    CardPropertyData* experience_ago;
    CardPropertyData* experience_after;
};

#endif /* defined(__FightPass__ExperienceEffect__) */
