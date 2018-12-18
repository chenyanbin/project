//
//  RefreshDot.hpp
//  FightPass
//
//  Created by 超 顾 on 16/3/3.
//
//

#ifndef RefreshDot_h
#define RefreshDot_h

#include "cocos2d.h"
#include "../BaseLayer.h"
USING_NS_CC;
class RefreshDot:public BaseLayer
{
public:
    RefreshDot();
    ~RefreshDot();
    static RefreshDot* getInstance();
    
    void requestMsg(Node* target,Point point,bool bol, int functionId1=0 ,int functionId2=0 ,int functionId3=0);
    void onRedMsgBack(EventCustom* msg);
private:
    void addEventListener();
    void removeEventListener();
private:
    Node* m_target;
    Point m_point;
    bool m_bol;
    int m_functionID1;
    int m_functionID2;
    int m_functionID3;
    static RefreshDot* _instance;
};

#endif /* RefreshDot_h */
