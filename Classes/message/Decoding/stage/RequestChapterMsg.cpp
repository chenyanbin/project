//
//  RequestChapterMsg.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/8/15.
//
//

#include "RequestChapterMsg.h"
#include "../../../commonData/GlobalInfo.h"
RequestChapterMsg::RequestChapterMsg(int chapterID)
:m_chapterID(chapterID)
{
    
}
RequestChapterMsg::~RequestChapterMsg()
{
    
}
ByteStream* RequestChapterMsg::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_BATTLE_ChapterPageReq);

  
    headBufferee->put(GlobalInfo::getInstance()->stageMode);
    headBufferee->putInt(m_chapterID);

    
    SetMessageLength();
}