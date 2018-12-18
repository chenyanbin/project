//
//  RequestChapterBoxMsg.h
//  FightPass
//
//  Created by zhangxiaobin on 15/8/15.
//
//

#ifndef __FightPass__RequestChapterBoxMsg__
#define __FightPass__RequestChapterBoxMsg__

#include "../MessageSendI.h"
class RequestChapterBoxMsg:public MessageSendI
{
public:
    RequestChapterBoxMsg(int boxID);
    ~RequestChapterBoxMsg();
    ByteStream *encodingData();
private:
    int m_boxID;
};
#endif /* defined(__FightPass__RequestChapterBoxMsg__) */
