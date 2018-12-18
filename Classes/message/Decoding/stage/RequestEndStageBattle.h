//
//  RequestEndStageBattle.h
//  FightPass
//
//  Created by zhangxiaobin on 15/8/18.
//
//

#ifndef __FightPass__RequestEndStageBattle__
#define __FightPass__RequestEndStageBattle__

#include "../MessageSendI.h"
class RequestEndStageBattle:public MessageSendI
{
public:
    //succ	是否成功	byte	Y	0失败 1成功
    RequestEndStageBattle(int battleID,bool isSuc,int starCount,int bloodBottle);
    ~RequestEndStageBattle();
    ByteStream *encodingData();
private:
    int m_battleID;
    bool m_isSuc;
    int m_starCount;
    int m_bloodBottle;
};

#endif /* defined(__FightPass__RequestEndStageBattle__) */
