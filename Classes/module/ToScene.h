//
//  ToScene.h
//  FightPass
//
//  Created by zhangxiaobin on 15/9/17.
//
//

#ifndef __FightPass__ToScene__
#define __FightPass__ToScene__

#include "BaseLayer.h"
class ToScene:public Scene
{
public:
    ToScene();
    ~ToScene();
    bool init(int openLayer = 0);
    static ToScene* create(int openLayer = 0);
    virtual void onEnter();
    virtual void onExit();
    
private:
    void openLayer();
private:
    int tag_openLayer;//场景转换后，要打开的界面
    
};

#endif /* defined(__FightPass__ToScene__) */
