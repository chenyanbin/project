//
//  GoRecharge.hpp
//  FightPass
//
//  Created by chenyanbin on 16/4/28.
//
//

#ifndef GoRecharge_hpp
#define GoRecharge_hpp

#include "cocos2d.h"
#include "../BaseLayer.h"
#include "../data/BaseTypeData.h"
class GoRecharge:public BaseLayer
{
public:
    
    GoRecharge();
    ~ GoRecharge();
    virtual bool init();
    static GoRecharge* create();
    static void show();
    
protected:
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
private:
    void onSetButton();
    void onClick(Ref* pSender);

};

#endif /* GoRecharge_hpp */
