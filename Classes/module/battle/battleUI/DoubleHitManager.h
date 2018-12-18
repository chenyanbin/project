//
//  DoubleHitManager.h
//  FightPass
//连击管理器
//  Created by zhangxiaobin on 15/7/9.
//
//

#ifndef __FightPass__DoubleHitManager__
#define __FightPass__DoubleHitManager__

#include "cocos2d.h"
USING_NS_CC;
class DoubleHitManager:public Node
{
public:
    DoubleHitManager();
    ~DoubleHitManager();
    static DoubleHitManager* getInstance();
public:
    void onHit();
private:
    void onClearCount();
    void addCount();
    
private:
    int m_count;
    float m_delayTime;
    static DoubleHitManager* _instance;
    std::queue<int>* countList;
    Sprite* bg;
private:
    int TAG_COUNT;
};

#endif /* defined(__FightPass__DoubleHitManager__) */
