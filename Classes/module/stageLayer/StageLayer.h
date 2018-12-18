//
//  StageLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/6/13.
//
//

#ifndef __FightPass__StageLayer__
#define __FightPass__StageLayer__

#include "../BaseLayer.h"

class StageLayer:public BaseLayer
{
public:
    StageLayer();
    ~StageLayer();
    virtual bool init();
    static StageLayer* create();
    static void show(int fromScene);
    static void requestChapterMsg();
protected:
    virtual void onEnter();
    virtual void onExit();
private:
    void setBackGround();
    void setUserHead();
    void setUserWealth();
    void setStageListLayer();
private:
    int TAG_USERHEAD;
    
};

#endif /* defined(__FightPass__StageLayer__) */
