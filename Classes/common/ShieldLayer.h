//
//  ShieldLayer.h
//  SuiTang
//屏蔽层。用于阻挡用户操作的层。此层透明。对玩家不能产生影响
//  Created by zhangxiaobin on 14-8-21.
//
//

#ifndef __SuiTang__ShieldLayer__
#define __SuiTang__ShieldLayer__

#include "../module/BaseLayer.h"
class ShieldLayer:public BaseLayer
{
public:
    ShieldLayer();
    ~ShieldLayer();
    virtual bool init();
    CREATE_FUNC(ShieldLayer);
protected:
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
private:
    void onDelay(float dt);
};

#endif /* defined(__SuiTang__ShieldLayer__) */
