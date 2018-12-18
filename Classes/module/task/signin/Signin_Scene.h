//
//  Signin_Scene.h
//  FightPass
//
//  Created by 超 顾 on 15/10/9.
//
//

#ifndef __FightPass__Signin_Scene__
#define __FightPass__Signin_Scene__
#include "extensions/cocos-ext.h"
#include "../../BaseLayer.h"
#include "cocos2d.h"
#include "../../../common/TouchSprite/Button.h"

USING_NS_CC_EXT;
USING_NS_CC;
class Signin_Scene:public BaseLayer
{
public:
    enum TAG_LAYER
    {
        TAG_DAYBENEFIT=100,//每日福利
        TAG_MONEYDRAWING,//招财
        TAG_EVERYDAY,//每日签到
        TAG_POWER,//体力
        TAG_LUXURY,//豪华签到
        TAG_WEEKBENEFIT,//每周福利
        
    };
    Signin_Scene();
    ~Signin_Scene();
    static Signin_Scene* create(int value);
    virtual bool init(int value);
    virtual void onEnter();
    virtual void onExit();
    void onEnterTransitionDidFinish();
    void onExitTransitionDidStart();
    static void show(int fromeScene = -1,int value = 1);
private:
    void createLayer();
    void topLayer();
    void combobox();
    void onComboBoxBtnClick(Ref* psender);
    void selectLayer(int num);
    void onMsgProcess(EventCustom* msg);
    void addEventListener();
    void removeEventListener();
    void onRefreshDot(EventCustom* msg);
private:
    int TAG_TOP;
    int TAG_COMBOBOX;
    
    int TAG_SELECTED;
    int TAG_MODULE;
    int TAG_MODULELABEL;
    
    int TAG_TABLEVIEW;
    int TAG_PERSON;
    Sprite* m_selected;
    Vector<Button*>* btnList;
    int select_id;
    int TAG_NODEBTN;
    float sx;
    
};

#endif /* defined(__FightPass__Signin_Scene__) */
