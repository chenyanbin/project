//
//  StageBattleInfo.hpp
//  FightPass
//
//  Created by zhangbin on 16/3/22.
//
//

#ifndef StageBattleInfo_hpp
#define StageBattleInfo_hpp

#include "cocos2d.h"
#include "../BaseLayer.h"
#include "../../net/bytestream.h"

typedef struct __BattleBoxData
{
    int canOpenCount;//可开宝箱数量
    int canOpenBoxId;//宝箱id
    int starCountMax;//最大星数
    int curStarCount;// 已经得星数
    int raidsCardCount;//扫荡令个数
}BattleBox;
class BattleData:public Ref
{
public:
    BattleData():battleId(0),starCount(0),usableCount(0),state(0)
    {
        
    }
    int battleId;//已通战斗关卡id
    int starCount;//已通子关卡关得星数
    int usableCount;//当日可用攻击次数，通关一次减1，第二日重置满值，0时不可进入
    int state;//status	状态	byte	Y	1 通过 2 可进入3 不可进入
};

class StageBattleInfo:public BaseLayer
{
public:
    StageBattleInfo();
    ~StageBattleInfo();
    virtual bool init(ByteStream* byteStream);
    static StageBattleInfo* create(ByteStream* byteStream);
    static void show(ByteStream* byteStream);
    void setGrayBg();
private:
    void setUserWealth();
    void parseByteStream(ByteStream* byteStream);
    void setInfoLayer();
    void setBoxLayer();
protected:
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual void addEventListener();
    virtual void removeEventListener();
private:
    BattleBox* boxData;
    Vector<BattleData*>* stageBattleList;
    int m_stageID;
private:
    int TAG_INFOLAYER;
};

#endif /* StageBattleInfo_hpp */
