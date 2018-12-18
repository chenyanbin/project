#ifndef __CCTOUCHSPRITE_H__
#define __CCTOUCHSPRITE_H__

#include "cocos2d.h"
USING_NS_CC;
class TouchSprite : public cocos2d::Sprite
{
public:
	TouchSprite();
	~TouchSprite();

	static TouchSprite* createWithPic(const char *fileName);
    //创建带有按下回调的方法
	static TouchSprite* createWithPic(const char *fileName,cocos2d::Ref *rec, cocos2d::SEL_CallFuncN selector);
	virtual void onEnter();
	virtual void onExit();
    virtual void setScale(float scale);
    //触摸就触发的回调
    void addTouchBegainCallBack(Ref* target,SEL_CallFuncN selector,int longPressType = 1);
    
    ccMenuCallback onMoveInCallBack;//移进按钮
    ccMenuCallback onMoveOutCallBack;//移出按钮
    ccMenuCallback onRelesaseOutCallBack;//按钮外抬起
    
    void setTouchMode(Touch::DispatchMode mode);
	virtual bool ccTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	virtual void ccTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	virtual void ccTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	virtual void ccTouchCancelled(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);

    virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);
    virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event);
    virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event);
    
    
	bool isDoubleClick;
    bool isButtonMode;
    float _isLongPress;//是否是长按(小于等于0 为不开始长按)
    Rect getRect(Node* spr);
    void setSwallowTouches(bool enabled);//是否屏蔽下层事件
    bool getIsMoveSprite();
    
protected:
	cocos2d::SEL_CallFuncN c_pfnSelector;
	cocos2d::Ref* m_pListener;
    
    cocos2d::SEL_CallFuncN c_touchBegainSelector;
	cocos2d::Ref* c_touchBegainTarget;
    EventListenerTouchOneByOne* touchListener;
    EventListenerTouchAllAtOnce* touchAllListener;
    bool isAllowTouches;//是否屏蔽下层事件
    bool isSuccessDelay;//是否成功延时(针对 在需要延时触摸  和 按下同时生效的时候)
    Touch::DispatchMode m_touchMode;
private:
	bool isMovedSprite;
	bool isClickSprite(cocos2d::Touch* pTouch);
    //长按模式的回调
    void longPressBack(float fd);
    float m_scale;
  
};

#endif