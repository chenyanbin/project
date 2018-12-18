//
//  PopupLoading.h
//  SuiTang
//
//  Created by zhangxiaobin on 14-7-18.
//资源加载loading
//

#ifndef __SuiTang__PopupLoading__
#define __SuiTang__PopupLoading__

#include "cocos2d.h"
USING_NS_CC;
#include "../../module/BaseLayer.h"
#include "../cutViewLayer/CutViewLayer.h"
class PopupLoading:public BaseLayer
{
public:
    PopupLoading();
    ~PopupLoading();
    virtual bool init(float timess);
    static PopupLoading* create(float timess);
    virtual void onEnter();
    virtual void onExit();
    void setProgressPercent(float progress);
    bool isAutoRemove;//是否自动删除
private:
    void setProgress();
private:
    void initLoading();
    void onDelay(float dt);
    void leftHandHit();
    void rightHandHit();
private:
    ProgressTimer* pt;
    Label* progressText;
    Node* m_dotContainer;
    
    int TAG_CONNECTWORD;
    
    int TAG_LEFTHAND;
    int TAG_RIGHTHAND;
};

#endif /* defined(__SuiTang__PopupLoading__) */
