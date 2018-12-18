//
//  MapProgressLayer.h
//  FightPass
//
//  Created by zhangxiaobin on 15/7/15.
//
//

#ifndef __FightPass__MapProgressLayer__
#define __FightPass__MapProgressLayer__

#include "cocos2d.h"
USING_NS_CC;
class MapProgressLayer:public Node
{
public:
    MapProgressLayer();
    ~MapProgressLayer();
    static MapProgressLayer* getInstance();
    void updateProgress(float percent);
protected:
    virtual void onEnter();
    virtual void onExit();
private:
    void setProgress();
private:
    static MapProgressLayer* _instance;
    Sprite* progressDot;
//    Sprite* progress;
    ProgressTimer* progressTimer;
};

#endif /* defined(__FightPass__MapProgressLayer__) */
