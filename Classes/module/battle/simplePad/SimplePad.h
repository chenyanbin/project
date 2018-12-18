//
//  SimplePad.h
//  FightPass
//
//  Created by zhangxiaobin on 15/5/24.
//
//

#ifndef __FightPass__SimplePad__
#define __FightPass__SimplePad__

#include "cocos2d.h"
USING_NS_CC;
#include "../../BaseLayer.h"
class SimplePad;
class SimplePadDelegate
{
public:
    virtual void didChangeDirectorTo(SimplePad* simplepad,Point direction) = 0;
    virtual void isHoldingDirector(SimplePad* simplepad,Point direction) = 0;
    virtual void simplePadTouchEnded(SimplePad* simplepad) = 0;
};
class SimplePad:public BaseLayer
{
public:
    SimplePad();
    ~SimplePad();
    bool init(const char* path,float radius);
    static SimplePad* create(const char* path,float radius);
    void setDelegate(SimplePadDelegate* delegate);
    void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);
    
    bool isHold;//是否一直按着
protected:
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    
    virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event);
    virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event);
    void update(float dt);
private:
    void updateDirectionForTouchLocation(Point location);//通标坐标算方向
    void setBackground(const char* path);
    bool isClickSprite(cocos2d::Touch* pTouch);
private:
    SimplePadDelegate* m_delegate;
    Sprite* handShank;
    float _radius; //半径
    Point _direction;//方向向量
    Point downStart;//按下初始位置
    bool m_isClickThis;//是否点击的自己
    int TAG_HANDBG;
    Size winSize;
    float sx;
    Point selfInitPoint;//自己初始坐标
};

#endif /* defined(__FightPass__SimplePad__) */
