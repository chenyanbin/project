//
//  CommonEffect.h
//  SuiTang
// UI界面普通特效
//  Created by zhangxiaobin on 14-9-29.
//
//

#ifndef __SuiTang__CommonEffect__
#define __SuiTang__CommonEffect__
#include "cocos2d.h"
USING_NS_CC;
#include "editor-support/cocostudio/CCArmature.h"
using namespace cocostudio;

class CommonEffect:public Node
{
public:
    CommonEffect();
    ~CommonEffect();
    bool init(const char* name,bool isLoop,bool isRemoveCache,std::function<void()> _callBack);
    static CommonEffect* create(const char* name,bool isLoop = true,bool isRemoveCache = true,std::function<void()> _callBack = NULL);
    virtual void release();
    virtual void setAnchorPoint(Point cp);
    Armature* getArmature();
    bool isAutoStop;//是否停在最后一帧
    std::function<void(Node*)> m_onFinisedcallback;
    ccMenuCallback onClick;
    //设置点击范围，相对于此目标
    void setClickOffsetRect(Rect rect);
    void removeSelf();
    void rePlay();
    static void pureCache(const char* name);
protected:
    void onEnter();
    void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    
    virtual bool ccTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
    virtual void ccTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
    virtual void ccTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);

    bool isClickSprite(cocos2d::Touch* pTouch);
    
   
    
private:
    void onDataLoaded(float percent);
    void removeCache();
    void onEffectMovementEvent(Armature *armature, MovementEventType type, const std::string& name);
    const char* m_name;
    bool m_isLoop;//是否循环播放
    bool m_isRemoveCache;
    Point m_anchorPoint;
    EventListenerTouchOneByOne* touchListener;
    Rect m_clickOffsetRect;//点击范围
    std::function<void()> m_callBack;//播放结束返回
private:
    int TAG_ARMATURE;
    
};

#endif /* defined(__SuiTang__CommonEffect__) */
