//
//  TipsLayer.hpp
//  FightPass
//
//  Created by zhangxiaobin on 15/11/3.
//
//

#ifndef TipsLayer_hpp
#define TipsLayer_hpp

#include "../BaseLayer.h"
class TipsLayer:public BaseLayer
{
public:
    TipsLayer();
    ~TipsLayer();
    virtual bool init();
    static void show(int conTypeId,int conId,int conVal);
    //物品的创建
    static TipsLayer* create(int conTypeId,int conId,int conVal);
public:
    void setItemData(int conTypeId,int conId,int conVal);
protected:
    
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
};

#endif /* TipsLayer_hpp */
