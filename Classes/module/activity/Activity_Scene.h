//
//  Activity_Scene.h
//  FightPass
//
//  Created by 超 顾 on 15/10/28.
//
//

#ifndef __FightPass__Activity_Scene__
#define __FightPass__Activity_Scene__

#include "extensions/cocos-ext.h"
#include "../BaseLayer.h"
#include "cocos2d.h"
#include "../../common/TouchSprite/Button.h"

USING_NS_CC_EXT;
USING_NS_CC;
class Activity_Scene:public BaseLayer
{
public:
    enum TAG_LAYER
    {
        TAG_SEVENACTIVITY=100,//七日活动
        TAG_FIRSTRECHARGE,//首冲
    };
    Activity_Scene();
    ~Activity_Scene();
    static Activity_Scene* create(int value);
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
    void removeEventListener();
    
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
    
    float sx;
    
};



#endif /* defined(__FightPass__Activity_Scene__) */
