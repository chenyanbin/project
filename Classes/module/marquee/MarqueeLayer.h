//
//  MarqueeLayer.h
//  SuiTang
//
//  Created by zhangxiaobin on 14/12/27.
//
//

#ifndef __SuiTang__MarqueeLayer__
#define __SuiTang__MarqueeLayer__

#include "../../common/cutViewLayer/CutViewLayer.h"
class MarqueeLayer:public CutViewLayer
{
public:
    MarqueeLayer();
    ~MarqueeLayer();
    virtual bool init();
    CREATE_FUNC(MarqueeLayer);
public:
    void addContent(int dictTipsID,std::string& paramsStr);
protected:
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
private:
    void onMoveEnd(Node* target);
private:
    Sprite* msgContainer;
};

#endif /* defined(__SuiTang__MarqueeLayer__) */
