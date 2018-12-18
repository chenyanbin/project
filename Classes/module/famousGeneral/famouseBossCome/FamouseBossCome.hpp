//
//  FamouseBossCome.hpp
//  FightPass
//名将来袭
//  Created by zhangxiaobin on 16/1/25.
//
//

#ifndef FamouseBossCome_hpp
#define FamouseBossCome_hpp

#include "../../BaseLayer.h"
class FamouseBossCome:public BaseLayer
{
public:
    FamouseBossCome();
    ~FamouseBossCome();
    virtual bool init();
    CREATE_FUNC(FamouseBossCome);
    static void show();
protected:
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual void addEventListener();
    virtual void removeEventListener();
private:
    void setInfo();
    void onEffectFinished(Node* pSender);
};

#endif /* FamouseBossCome_hpp */
