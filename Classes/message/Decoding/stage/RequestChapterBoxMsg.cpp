//
//  RequestChapterBoxMsg.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/8/15.
//
//

#include "RequestChapterBoxMsg.h"
#include "../../../commonData/GlobalInfo.h"
RequestChapterBoxMsg::RequestChapterBoxMsg(int boxID)
:m_boxID(boxID)
{
    
}
RequestChapterBoxMsg::~RequestChapterBoxMsg()
{
    
}
ByteStream * RequestChapterBoxMsg::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_BATTLE_ChapterOpenBoxReq);
    
    headBufferee->put(GlobalInfo::getInstance()->stageMode);
    headBufferee->putInt(m_boxID);
    
    
    SetMessageLength();
}