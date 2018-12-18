//
//  FogLayer.h
//  SuiTang
//
//  Created by zhangxiaobin on 14-10-16.
//烟雾层
//

#ifndef __SuiTang__FogLayer__
#define __SuiTang__FogLayer__

#include "../module/BaseLayer.h"
class FogLayer:public BaseLayer
{
public:
    FogLayer();
    ~FogLayer();
    virtual bool init(float delayTime,const std::function<void()> &func);
    static FogLayer* create(float delayTime,const std::function<void()> &func);
   
protected:
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
private:
    void setFogLayer();
    void onDelayEnd();
private:
    float _delayTime;
    std::function<void()> _function;
};

#endif /* defined(__SuiTang__FogLayer__) */
