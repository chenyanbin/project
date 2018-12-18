//
//  LoadingPage.hpp
//  FightPass
//
//  Created by zhangxiaobin on 15/12/2.
//
//

#ifndef LoadingPage_hpp
#define LoadingPage_hpp

#include "cocos2d.h"
USING_NS_CC;
#include "../../module/BaseLayer.h"

class LoadingPage:public BaseLayer
{
public:
    LoadingPage();
    ~LoadingPage();
    virtual bool init();
    static LoadingPage* create();
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    void setProgressPercent(float progress);
    
private:
    void setProgressCircle();
    void setBlackBg();
    void setDrum();
    void leftHandHit();
    void rightHandHit();
    void setLoadingText();
private:
    ProgressTimer* pt;
    Label* progressText;
    Node* drumSpr;
    int m_textIndex;
    Sprite* loadingText;
    int TAG_CONNECTWORD;
    int TAG_LEFTHAND;
    int TAG_RIGHTHAND;
};


#endif /* LoadingPage_hpp */
