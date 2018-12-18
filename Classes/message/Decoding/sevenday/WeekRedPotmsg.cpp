//
//  WeekRedPotmsg.cpp
//  FightPass
//
//  Created by chenyanbin on 16/4/29.
//
//

#include "WeekRedPotmsg.hpp"
WeekRedPotmsg::WeekRedPotmsg()
{
    
}
WeekRedPotmsg::~ WeekRedPotmsg()
{
    
}
ByteStream* WeekRedPotmsg::encodingData()
{
    MessageSendI::encodingData(SCENSE_CLIENT_WEEK_WeekRedPointStatusReq);
    //    headBufferee->put(m_function);
    
    SetMessageLength();
}