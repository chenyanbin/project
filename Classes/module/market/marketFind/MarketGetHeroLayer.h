//
//  MarketGetHeroLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/8/7.
//
//

#ifndef __FightPass__MarketGetHeroLayer__
#define __FightPass__MarketGetHeroLayer__

#include "../../BaseLayer.h"
#include "editor-support/cocostudio/CCArmature.h"
using namespace cocostudio;

#include "../marketData/MarketFindResultDataManager.h"
class MarketGetHeroLayer:public BaseLayer
{
public:
    MarketGetHeroLayer();
    ~MarketGetHeroLayer();
    virtual bool init(MarketFindResultData* finddata,std::function<void()> _callBack);
    static MarketGetHeroLayer* create(MarketFindResultData* finddata,std::function<void()> _callBack = NULL);
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    static void show(MarketFindResultData* finddata,std::function<void()> _callBack = NULL);
protected:
    virtual void backScene();
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
private:
    void setBackground();
    void onRotateEnded();//旋转结束
    void setGetCard();
    void setParticle();
    void clearResourcePerson();
    void setParticle1();
    void setclearPatticle();
    void setclearPatticle2();
    void setclearPatticle3();
    void setChangeCard();
    void loadPerson();
    void onDataLoaded(float percent);
    void updateStarLevel();
private:
    int TAG_PATTICLE;
    int TAG_CARDBG;
    int TAG_PARTICLE2;
    int TAG_PARTICLE3;
    bool isAnimationEnded;//动画是否播放结束
    MarketFindResultData* m_findData;
    std::function<void()> m_callBack;
    int TAG_PRESTLABEL;
};


#endif /* defined(__FightPass__MarketGetHeroLayer__) */
