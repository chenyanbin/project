//
//  PopUpLayer.h
//  SuiTang
//
//  Created by mac on 14-6-26.
//
//

#ifndef __SuiTang__PopUpLayer__
#define __SuiTang__PopUpLayer__

#include "cocos2d.h"
USING_NS_CC;
#include "../../module/BaseLayer.h"
class PopUpLayer :public BaseLayer
{
public:
    PopUpLayer();
    ~PopUpLayer();
    virtual bool init();
    CREATE_FUNC(PopUpLayer);

    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
protected:
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
public:
     void close();
     void setCallBack(Ref* listener,SEL_CallFuncN callBack);
     void addButton(const char* path,int tag,const char* btnBg=IMG_BUTTON_TWO_BLUEBTN1);
     void setContent(const char* msg);
    void setTitle(const char* msg);
public:
    bool isAutoClose;// 是否自动关闭
private:
    Menu* menu;
    void onMenuClick(Ref* pSender);
    
private:
    Ref* m_callbackListener;
    SEL_CallFuncN m_callback;
    int TAG_LABEL;

};

#endif /* defined(__SuiTang__PopUpLayer__) */
