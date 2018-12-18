//
//  AwardBox_Layer.h
//  FightPass
//
//  Created by 超 顾 on 15/12/7.
//
//

#ifndef __FightPass__AwardBox_Layer__
#define __FightPass__AwardBox_Layer__

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../BaseLayer.h"
#include "../data/BaseTypeData.h"
USING_NS_CC_EXT;
USING_NS_CC;
class AwardBox_Layer:public BaseLayer
{
public:
    AwardBox_Layer();
    ~AwardBox_Layer();
    virtual void onExit();
    virtual void onEnter();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual bool init(Vector<BaseTypeData*> *m_baseList);
    static AwardBox_Layer* create(Vector<BaseTypeData*> *m_baseList);
private:
    void createLayer();
    void showAwardBoxSound();
private:
    float sx;
    int TAG_ITEMS;
    Vector<BaseTypeData*> *m_list;
};
#endif /* defined(__FightPass__AwardBox_Layer__) */
