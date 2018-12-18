//
//  RequestChapterMsg.h
//  FightPass
//
//  Created by zhangxiaobin on 15/8/15.
//
//

#ifndef __FightPass__RequestChapterMsg__
#define __FightPass__RequestChapterMsg__

#include "../MessageSendI.h"
class RequestChapterMsg:public MessageSendI
{
public:
    RequestChapterMsg(int chapterID);
    ~RequestChapterMsg();
    ByteStream *encodingData();
private:
    int m_chapterID;
    
};


#endif /* defined(__FightPass__RequestChapterMsg__) */
