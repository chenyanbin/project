//
//  LimitCardSkillLayer.h
//  FightPass
//
//  Created by chenyanbin on 16/1/4.
//
//

#ifndef __FightPass__LimitCardSkillLayer__
#define __FightPass__LimitCardSkillLayer__

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../BaseLayer.h"

USING_NS_CC_EXT;
USING_NS_CC;
class LimitCardSkillLayer:public BaseLayer
{
public:
    LimitCardSkillLayer();
    ~ LimitCardSkillLayer();
    virtual void onExit();
    virtual void onEnter();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual bool init(int _skill1, int _skill2, int _skill3, int _skill4 );
    static LimitCardSkillLayer* create(int _skill1, int _skill2, int _skill3, int _skill4 );
    static void show(int _skill1, int _skill2, int _skill3, int _skill4 );
private:
    void createLayer(int _skill1, int _skill2, int _skill3, int _skill4 );
    Sprite* setskilldesc(int index,int _skill);
   
private:
    float sx;
    
};
#endif /* defined(__FightPass__LimitCardSkillLayer__) */

