//
//  PowerLayer.hpp
//  FightPass
//
//  Created by chenyanbin on 16/3/16.
//
//   体力

#ifndef PowerLayer_hpp
#define PowerLayer_hpp

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../../../BaseLayer.h"
USING_NS_CC_EXT;
USING_NS_CC;
class PowerLayer:public BaseLayer
{
public:
    enum TAG_STATUS
    {
        TAG_NOLINQU = 100,
        TAG_UNTIME ,
        TAG_SUCCEEDLINQU
    };
    PowerLayer();
    ~PowerLayer();
    
    virtual bool init();
    static PowerLayer* create();
private:
    void createLayer();
    void onPersonClick(Ref* pSender);
    void setReceiveMessage(int _status,long _nowTime);
    
    void requestPowerMsg();//获取体力
    void onPowerMsgProcess(EventCustom* msg);
    void addEventListener();
    void removeEventListener();
    
    void requestPowerPageMsg();//体力页
protected:
    virtual void onExit();
    virtual void onEnter();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
private:
    float sx;
    int TAG_RECEIVEBTN;
    int m_status;
    long m_nowTime;
    int powecount;
    int TAG_POWERLABEL;
    bool m_isReceive;
};

#endif /* PowerLayer_hpp */
