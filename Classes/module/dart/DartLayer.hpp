//
//  DartLayer.hpp
//  FightPass
//
//  Created by chenyanbin on 16/4/7.
//
//

#ifndef DartLayer_hpp
#define DartLayer_hpp

#include "cocos2d.h"
#include "../BaseLayer.h"
#include "../data/BaseTypeData.h"
class DartLayer:public BaseLayer
{
public:
    
    DartLayer();
    ~ DartLayer();
    virtual bool init();
    static DartLayer* create();
    static void show();
    
protected:
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual void addEventListener();
    virtual void removeEventListener();
private:
    void onSetButton();
    void onSetContent(int count,int allCount,int glod);

    void onclick(Ref* psender);
    
    void requestDarPagetMsg();
    void onDartPageMsgProcess(EventCustom* msg);
    
    void requestDarMsg();
    void setBoom(int multiple);
private:
    int TAG_NODE;
    int m_allCount;
    int coustGold;
};

#endif /* DartLayer_hpp */
