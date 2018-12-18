//
//  HomeMenuBar.h
//  SuiTang
//
//  Created by zhangxiaobin on 14/11/6.
//
//

#ifndef __SuiTang__HomeMenuBar__
#define __SuiTang__HomeMenuBar__

#include "cocos2d.h"
#include "../../../../common/TouchSprite/Button.h"
#include "../../../BaseLayer.h"
USING_NS_CC;
using namespace std;
class HomeMenuBar:public BaseLayer
{
public:
    HomeMenuBar();
    ~HomeMenuBar();
    virtual bool init();
    CREATE_FUNC(HomeMenuBar);
    void openMenuBar(Ref* pSender = NULL);
    void closeMenuBar(Ref* pSender = NULL);
    
    //显示关卡操作按钮    
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    
 private:
    virtual void addEventListener();
    virtual void removeEventListener();
    
private:
    void setSwitchBtn();//设置开关按钮
    void closeVerticalMenu();
    void openVerticalMenu();
    void initBG();
    void setMenuList();//横的列表
    void setVerticalList();//竖的列表
    void onMenuClick(Ref* pSender);
    void onActiveClick(Node* pSender);
    void onBayeClick(Node* pSender);
    void onMoveEnd(Ref* target);
    void barAction();
    void barAction2();
    void barAction3();
    void setBarVisible(Node* node);
    //图标状态
    void onStateChanged(int type);
    //新功能开启
    void onNewFunctionOpen(EventCustom* event);
    void setPrayTime();
    void onRefreshDot(EventCustom* msg);
private:
    int TAG_BG;
    int TAG_MENU;
    int TAG_VERTICAL_MENU;
    int TAG_SWITCH_MENU;
    int TAG_OPENBTN;
    int TAG_CLOSEBTN;
    int TAG_SWITCHBTN;
    int TAG_BOOKBTN;
    float sx;
    bool bookStatus;
    int firstBtnNum;
private:
    //按钮总个数
    int MENUCOUNT;
    int VERTICALCOUNT;
    int menuID[8];
    
    int menuY;
    vector<Point>* pointList;
    Vector<Button*>* btnList;
//    Vector<Point>
    int TAG_LEFTTIME;
    int m_time;
};
#endif /* defined(__SuiTang__HomeMenuBar__) */
