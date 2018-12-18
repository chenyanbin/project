//
//  MusouBattleLayer.h
//  FightPass
//
//  Created by zhangxiaobin on 15/9/18.
//
//

#ifndef __FightPass__MusouBattleLayer__
#define __FightPass__MusouBattleLayer__

#include "../BaseLayer.h"
#include "MusouBattleList.h"
#include "../../net/bytestream.h"
#include "MusouBattleData.h"
class MusouBattleLayer:public BaseLayer
{
public:
    MusouBattleLayer();
    ~MusouBattleLayer();
    virtual bool init(ByteStream* byteStream);
    static MusouBattleLayer* create(ByteStream* byteStream);
    static void show(ByteStream* byteStream);
    static void requestBattleList(int stageID);
    
private:
    void setBg();
    void setUserWealth();
    void setBattleList();
    void setLeftTime();
    void parseByteStream(ByteStream* byteStream);
    
    void showDelayTime(float dt);
private:
    int m_leftTime;
    Vector<MusouBattleData*>* battleList;
private:
    int TAG_LEFTTIME;
    int TAG_BATTLELIST;
};


#endif /* defined(__FightPass__MusouBattleLayer__) */
