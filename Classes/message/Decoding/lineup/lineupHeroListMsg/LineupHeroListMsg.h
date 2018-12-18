//
//  LineupHeroListMsg.h
//  FightPass
//
//  Created by chenyanbin on 15/8/10.
//
//

#ifndef __FightPass__LineupHeroListMsg__
#define __FightPass__LineupHeroListMsg__

#include "../../MessageSendI.h"
class LineupHeroListMsg:public MessageSendI
{
public:
    LineupHeroListMsg(int _lineupId,int _fromHeroType,int _fromLocation);
    ~LineupHeroListMsg();
    ByteStream *encodingData();
private:
    int lineupId;//阵容编号
    int fromHeroType;//武将类型
    int fromLocation;//位置
};

#endif /* defined(__FightPass__LineupHeroListMsg__) */
