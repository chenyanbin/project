//
//  GuideScene.h
//  SuiTang
//
//  Created by zhangxiaobin on 14-9-10.
//
//

#ifndef __SuiTang__GuideScene__
#define __SuiTang__GuideScene__

#include "../BaseLayer.h"
#include "../../commonData/dictData/DictNewGuide/DictNewGuideManager.h"
#include "editor-support/cocostudio/CCArmature.h"
using namespace cocostudio;
#include "../../common/commonEffect/CommonEffect.h"
class GuideScene:public BaseLayer
{
public:
    GuideScene();
    ~GuideScene();
    virtual bool init();
    CREATE_FUNC(GuideScene);

public:
    void updateGuideData(DictNewGuide* dictNewGuide);
    void hideArrow();
private:
    void onDataLoaded(float percent);
    void setBg();//
    void autoArrowPosition(Point cp);
    void setTouchIsAllow(Point cp);
    void setScaleMode();
    void setClipNode();
    DrawNode* getDrawNode();
protected:
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
private:
    void setAbleTouch();
    void setSkillArrow();
  private:
    DictNewGuide* m_guideData;
    bool isAbleClick;
    bool isClickArea;//是否点击在点击区域
    float initScaleY;
    Node* arrow;
    Armature* handEffect;
    Sprite* skillArrow;
    int TAG_CLIPNODE;
};

#endif /* defined(__SuiTang__GuideScene__) */
