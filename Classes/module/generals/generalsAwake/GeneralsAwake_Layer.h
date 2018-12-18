//
//  GeneralsAwake_Layer.h
//  FightPass
//
//  Created by 超 顾 on 15/12/2.
//不用这个类了。
//

#ifndef __FightPass__GeneralsAwake_Layer__
#define __FightPass__GeneralsAwake_Layer__

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../../BaseLayer.h"
#include "../data/CardPropertyData.h"
USING_NS_CC_EXT;
USING_NS_CC;
class AwakeData:public Ref
{
public:
    int canWakeUp;//是否能觉醒，0:No，1:yes
    int needStoneId;//觉醒石ID
    string needStoneName;//觉醒石名字
    int needStoneQuality;//觉醒石品质
    int needStoneCount;//需要觉醒石数量
    int ownStoneCount;//觉醒石总数量
    int needCoin;//花费
};
class GeneralsAwake_Layer:public BaseLayer
{
public:
    GeneralsAwake_Layer();
    ~GeneralsAwake_Layer();
    virtual void onExit();
    virtual void onEnter();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual bool init();
    CREATE_FUNC(GeneralsAwake_Layer);
    
private:
    void createLayer();
    void requestListMsg();
    void requestUpMsg();
    void onMsgProcess(EventCustom* msg);
    void addEventListener();
    void removeEventListener();
    void onBtnClick(Ref* pSender);
private:
    float sx;
    AwakeData* m_awakeData;
    int TAG_AWAKEN;
    int TAG_NODEBG;
};


#endif /* defined(__FightPass__GeneralsAwake_Layer__) */
