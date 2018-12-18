//
//  EnterGameLayer.h
//  FightPass
//
//  Created by zhangxiaobin on 15/7/21.
//
//

#ifndef __FightPass__EnterGameLayer__
#define __FightPass__EnterGameLayer__

#include "../../BaseLayer.h"
class EnterGameLayer:public BaseLayer
{
public:
    EnterGameLayer();
    ~EnterGameLayer();
    virtual bool init();
    CREATE_FUNC(EnterGameLayer);
    static void show();
    static void hide();
private:
    void setBg();
    void onEnterGame(Ref* pSender);
    void setLogo();
    void onSelectedServer(Node* pSender);
    
};

#endif /* defined(__FightPass__EnterGameLayer__) */
