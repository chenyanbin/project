//
//  SweepLayer.h
//  FightPass
//此模块已经没用了。用stageBattleInfo替换了。。
//  Created by chenyanbin on 15/7/1.
//
//

#ifndef __FightPass__SweepLayer__
#define __FightPass__SweepLayer__

#include "cocos2d.h"
#include "../BaseLayer.h"
#include "../../net/bytestream.h"
typedef struct _BattleBoxData
{
    int canOpenCount;//可开宝箱数量
    int canOpenBoxId;//宝箱id
    int starCountMax;//最大星数
    int curStarCount;// 已经得星数
    int raidsCardCount;//扫荡令个数
} BattleBoxData;
class StageBattleData:public Ref
{
public:
    StageBattleData():battleId(0),starCount(0),usableCount(0),state(0)
    {
        
    }
    int battleId;//已通战斗关卡id
    int starCount;//已通子关卡关得星数
    int usableCount;//当日可用攻击次数，通关一次减1，第二日重置满值，0时不可进入
    int state;//status	状态	byte	Y	1 通过 2 可进入3 不可进入
};
class SweepLayer:public BaseLayer
{
public:
    SweepLayer();
    ~SweepLayer();
    virtual bool init(ByteStream* byteStream);
    static SweepLayer* create(ByteStream* byteStream);
    static void show(ByteStream* byteStream);
    void setGrayBg();

protected:
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual void addEventListener();
    virtual void removeEventListener();
private:
    void setBackGround();
    void setUserHead();
    void setUserWealth();
    void setCardLayer();
    void setBoxLayer();
    void parseByteStream(ByteStream* byteStream);
   
private:
    BattleBoxData* boxData;
    Vector<StageBattleData*>* stageBattleList;
    int m_stageID;
    int TAG_USERHEAD;
    
    
};


#endif /* defined(__FightPass__SweepLayer__) */
