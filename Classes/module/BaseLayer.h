
//

//					 _oo0oo_
//					o8888888o
//					88" . "88
//					(| -_- |)
//					0\  =  /0
//				  ___/`---'\___
//				.' \\|     |-- '.
//			   / \\|||  :  |||-- \
//		 	  / _||||| -:- |||||- \
//			 |   | \\\  -  --/ |   |
//			 | \_|  ''\---/''  |_/ |
// 			 \  .-\__  '-'  ___/-. /
// 			___'. .'  /--.--\  `. .'___
//		 ."" '<  `.___\_<|>_/___.' >' "".
//	   | | :  `- \`.;`\ _ /`;.`/ - ` : | |
//     \  \ `_.   \_ __\ /__ _/   .-` /  /
// =====`-.____`.___ \_____/___.-`___.-'=====
//					 `=---='
// 	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//		   佛祖保佑   永无BUG   永不修改
//  BaseLayer.h
//  //
//  Created by mac on 14-4-25.
//
//

#ifndef __SuiTang__BaseLayer__
#define __SuiTang__BaseLayer__

#include "cocos2d.h"
USING_NS_CC;
#include "../common/ImagePath.h"
#include "../common/PublicShowUI.h"
#include "../VisibleRect.h"
#include "../commonData/GlobalInfo.h"
#include "../common/GameConfig.h"
#include "../soundManager/SoundManager.h"
#include "../commonData/data/GuideButtonManager.h"
class BaseLayer:public Layer
{
public:
    BaseLayer();
    ~BaseLayer();
    virtual bool init();
    virtual void setBackground(const char* path = NULL,Point anchorPoint = Point(0,0),bool isAutoScale = true);
    void setBackBtn(float offX = -10,float offY = -10,bool autoScale = true);
    
    virtual void backScene();
    void setFromScene(int fromScene = SCENE_TAG_INIT);
    int getFromScene();
    void setClickEnabled(bool enabled,int proprity = 0);//单点触摸
    void setTouchAllEnabled(bool enabled);//多点触摸
    void onBackClick(Ref* pSender = NULL);
    virtual void setGrayBg();
    void setOffsetGrayBg();
    void removeGrayBg();
//    void setNewGuidePosition(Point cp);//设置新手引导箭头位置
    void broadMsg(const char* msg, void* _userData = NULL);
protected:
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    
    virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);
    virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event);
    virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event);
 
    
    virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
    
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual void addEventListener();
    virtual void removeEventListener();
    
    void addUserMsg(const char* msg,const std::function<void(EventCustom*)>& callback);
    
    void addPvrPlist(const char* plistPath);//加载模块资源
    
protected:
    int m_fromScene;
    EventListenerTouchOneByOne* m_eventDispatcher;//单点触摸
    EventListenerTouchAllAtOnce* m_touchAllDispatcher;//多点触摸
    EventListenerKeyboard* keyboardListener;
    bool isTouchBegainThis;//是否从自己点击触发
public:
    bool isAnimation;
    bool isShowGrayBg;//是否显示灰背景
    bool isClickClose;//是否在点击框外，自动关闭
    bool isAbleGuiding;//是否可以引导
    bool isShowOpenSound;//是否播放打开音效
    bool isAutoReleasePlist;//是否自动删除plist
    bool isHideSceneFun;//是否隐藏场景功能
protected:
    int TAG_BG;
    int TAG_BACKBTN;
    int TAG_BLACKBG;//弹框半透明黑影
    
    vector<string> userMsgList;
    string m_pvrPlistPath;
};

#endif /* defined(__TwoMahjong__BaseLayer__) */
