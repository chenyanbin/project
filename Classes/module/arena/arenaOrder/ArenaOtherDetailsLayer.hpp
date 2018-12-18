//
//  ArenaOtherDetailsLayer.hpp
//  FightPass
//
//  Created by chenyanbin on 16/3/22.
//
// 查看其它

#ifndef ArenaOtherDetailsLayer_hpp
#define ArenaOtherDetailsLayer_hpp

#include "../../BaseLayer.h"
class ArenaOtherDetailsLayer:public BaseLayer
{
public:
    ArenaOtherDetailsLayer();
    ~ ArenaOtherDetailsLayer();
    virtual bool init(int idType,int roleId);
    static ArenaOtherDetailsLayer* create(int idType,int roleId);
    static void show(int idType,int roleId);
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
private:
    void setBgLayer();
    void setHeroHead();
    void setOneHeroMessage(int index);
    void onUserClick(Node* pSender);
    
    void requestAccelerMsg(int m_idType,long roleId);
    void onAccelerMsgProcess(EventCustom* msg);
    void addEventListener();
    void removeEventListener();
    
private:
    int m_nowcount;
    int TAG_COUNT;
    int TAG_ALLCOUNT;
    int m_roleId;
    int m_owngold;//总元宝
    int TAG_NODE;
};


#endif /* ArenaOtherDetailsLayer_hpp */
