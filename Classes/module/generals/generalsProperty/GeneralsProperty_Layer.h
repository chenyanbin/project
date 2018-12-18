//
//  GeneralsProperty_Layer.h
//  FightPass
//
//  Created by 超 顾 on 15/8/3.
//
//

#ifndef __FightPass__GeneralsProperty_Layer__
#define __FightPass__GeneralsProperty_Layer__

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../../BaseLayer.h"
#include "../data/CardPropertyData.h"
USING_NS_CC_EXT;
USING_NS_CC;
class GeneralsProperty_Layer:public BaseLayer
{
public:
    GeneralsProperty_Layer();
    ~GeneralsProperty_Layer();
    virtual void onExit();
    virtual void onEnter();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual bool init();
    CREATE_FUNC(GeneralsProperty_Layer);
private:
    void createLayer();
    void requestListMsg();
    void onMsgProcess(EventCustom* msg);
    void addEventListener();
    void removeEventListener();
private:
    float sx;
    CardPropertyData* propertyData;
};

#endif /* defined(__FightPass__GeneralsProperty_Layer__) */
