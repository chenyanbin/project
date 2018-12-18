//
//  ArenaExplainLayer.hpp
//  FightPass
//
//  Created by chenyanbin on 16/3/30.
//
//

#ifndef ArenaExplainLayer_hpp
#define ArenaExplainLayer_hpp

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../BaseLayer.h"

USING_NS_CC_EXT;
USING_NS_CC;
class ArenaExplainLayer:public BaseLayer
{
public:
    ArenaExplainLayer();
    ~ ArenaExplainLayer();
    virtual void onExit();
    virtual void onEnter();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual bool init();
    static ArenaExplainLayer* create( );
    static void show();
private:
    void createLayer( );
    
private:
    float sx;
    
};

#endif /* ArenaExplainLayer_hpp */
