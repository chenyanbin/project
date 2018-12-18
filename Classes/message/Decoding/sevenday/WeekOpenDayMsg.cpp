//
//  WeekOpenDayMsg.cpp
//  FightPass
//
//  Created by chenyanbin on 15/11/26.
//
//

#include "WeekOpenDayMsg.h"
WeekOpenDayMsg::WeekOpenDayMsg()
{
    
}
WeekOpenDayMsg::~ WeekOpenDayMsg()
{
    
}
ByteStream* WeekOpenDayMsg::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_WEEK_WeekOpenDayReq);
    //    headBufferee->put(m_function);
    
    SetMessageLength();
}